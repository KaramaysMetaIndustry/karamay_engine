#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer.h"
#include "graphics/variable/glsl_types.h"

namespace gl_vertex_array_enum
{
	enum class attribute_component_type
	{
		BYTE = GL_BYTE, //=>
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE, //=> glsl_bool
		SHORT = GL_SHORT, 
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT,
		INT = GL_INT, //=> glsl_int
		UNSIGNED_INT = GL_UNSIGNED_INT, //=> glsl_uint
		// glVertexAttribPointer
		// glVertexAttribIPointer

		HALF_FLOAT = GL_HALF_FLOAT, 
		FLOAT = GL_FLOAT, //=> glsl_float
		FIXED = GL_FIXED, 
		INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
		UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
		UNSIGNED_INT_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV,
		//glVertexAttribPointer

		DOUBLE = GL_DOUBLE, //=> glsl_double
		//glVertexAttribPointer
		//glVertexAttribLPointer
	};
}


struct gl_vertex_attribute_layout
{
	std::uint32_t attribs_num;
	std::uint32_t attrib_size;
	std::uint32_t components_num;
	std::uint32_t components_type_enum;
	std::uint8_t normalized;
	std::uint32_t divisor;

	gl_vertex_attribute_layout() :
		attribs_num(0),
		attrib_size(0),
		components_num(0),
		components_type_enum(0),
		normalized(false),
		divisor(0)
	{
	}
};

class gl_vertex_array_descriptor final
{
public:

	gl_vertex_array_descriptor()
	{}

	~gl_vertex_array_descriptor()
	{}

public:

	template<typename T>
	void add_attributes(const std::vector<T>& attributes)
	{
		static_assert(
			std::is_same<glv_ivec1, T>::value ||
			std::is_same<glv_ivec2, T>::value ||
			std::is_same<glv_ivec3, T>::value ||
			std::is_same<glv_ivec4, T>::value || // int
			std::is_same<glv_uvec1, T>::value ||
			std::is_same<glv_uvec2, T>::value ||
			std::is_same<glv_uvec3, T>::value ||
			std::is_same<glv_uvec4, T>::value || // uint
			std::is_same<glv_vec1, T>::value ||
			std::is_same<glv_vec2, T>::value ||
			std::is_same<glv_vec3, T>::value ||
			std::is_same<glv_vec4, T>::value || // float
			std::is_same<glv_dvec1, T>::value ||
			std::is_same<glv_dvec2, T>::value ||
			std::is_same<glv_dvec3, T>::value ||
			std::is_same<glv_dvec4, T>::value || // double
			std::is_same<glv_mat2, T>::value ||
			std::is_same<glv_mat2x3, T>::value ||
			std::is_same<glv_mat2x4, T>::value ||
			std::is_same<glv_mat3, T>::value ||
			std::is_same<glv_mat3x2, T>::value ||
			std::is_same<glv_mat3x4, T>::value ||
			std::is_same<glv_mat4, T>::value ||
			std::is_same<glv_mat4x2, T>::value ||
			std::is_same<glv_mat4x3, T>::value || // float
			std::is_same<glv_dmat2, T>::value ||
			std::is_same<glv_dmat2x3, T>::value ||
			std::is_same<glv_dmat2x4, T>::value ||
			std::is_same<glv_dmat3, T>::value ||
			std::is_same<glv_dmat3x2, T>::value ||
			std::is_same<glv_dmat3x4, T>::value ||
			std::is_same<glv_dmat4, T>::value ||
			std::is_same<glv_dmat4x2, T>::value ||
			std::is_same<glv_dmat4x3, T>::value    // double
			, "T must be glv_* types.");
		
		
		const std::uint8_t* _bytes = (std::uint8_t*)attributes.data();
		const std::size_t _size = attributes.size() * sizeof(T);
		for (std::size_t i = 0; i < _size; ++i)
		{
			_data.push_back(_bytes[i]);
		}

		gl_vertex_attribute_layout _layout;
		_layout.components_num = T::length();
		_layout.components_type_enum = _get_component_type_enum<T::value_type>();
		_layout.attrib_size = sizeof(T);
		_layout.attribs_num = static_cast<std::uint32_t>(attributes.size());
		_layouts.push_back(_layout);

		_is_dirty = true;
	}

	template<typename T>
	void add_attributes_instanced(const std::vector<T>& attributes, std::uint32_t divisor)
	{
		glVertexAttribFormat()
	}


	
	

private:

	template<typename T>
	inline std::uint32_t _get_component_type_enum() { return 0; }
	template<>
	inline std::uint32_t _get_component_type_enum<glv_ivec1::value_type>() { return GL_INT; }
	template<>
	inline std::uint32_t _get_component_type_enum<glv_uvec1::value_type>() { return GL_UNSIGNED_INT; }
	template<>
	inline std::uint32_t _get_component_type_enum<glv_vec1::value_type>() { return GL_FLOAT; }
	template<>
	inline std::uint32_t _get_component_type_enum<glv_dvec1::value_type>() { return GL_DOUBLE; }
	
public:

	const void* get_data() const;

	const std::size_t get_data_size() const;

	const std::vector<gl_vertex_attribute_layout> get_layouts() const;

	const bool is_dirty() const
	{
		return _is_dirty;
	}

	void clear_dirty()
	{
		_is_dirty = false;
	}

private:

	std::vector<std::uint8_t> _data;

	std::vector<gl_vertex_attribute_layout> _layouts;

	std::uint8_t _is_dirty : 1;

};


class gl_vertex_array final : public gl_object
{
public:

	gl_vertex_array(std::shared_ptr<gl_vertex_array_descriptor> descriptor)
	{
		glCreateVertexArrays(1, &_handle);

		_descriptor = descriptor;

		if (_descriptor && _descriptor->is_dirty())
		{
			_fill();
		}
	}

	virtual ~gl_vertex_array()
	{
		glDeleteVertexArrays(1, &_handle);
	}

public:

	void tick(std::float_t delta_time);

	void bind();

	void unbind();

	void enable_pointers();

	void disable_pointers();

private:

	inline void _bind_buffer()
	{
		if (_buffer)
			glBindBuffer(GL_ARRAY_BUFFER, _buffer->get_handle());
	}

	inline void _unbind_buffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void _fill()
	{
#define ATTRIBUTE_OFFSET(OFFSET) (const void*)(OFFSET)

		if (_descriptor)
		{
			const auto _data_size = _descriptor->get_data_size();
			const auto& _layouts = _descriptor->get_layouts();
			{
				_buffer = std::make_shared<gl_buffer>();
				_buffer->allocate(_data_size);
				_buffer->fill(0, _data_size, _descriptor->get_data());
			}

			bind(); _bind_buffer(); // bind vertex array && bind buffer

			const std::uint32_t _max_pointer_index_num = static_cast<std::uint32_t>(_layouts.size());
			std::size_t _offset = 0;

			for (std::uint32_t i = 0; i < _max_pointer_index_num; ++i)
			{
				const auto& _layout = _layouts[i];
				const auto _type = _layout.components_type_enum;
				
				glEnableVertexAttribArray(i); // enable
				// set pointer
				if (_type == GL_BYTE || _type == GL_UNSIGNED_BYTE ||
					_type == GL_SHORT || _type == GL_UNSIGNED_SHORT ||
					_type == GL_INT || _type == GL_UNSIGNED_INT)
				{
					glVertexAttribIPointer(i,
						_layout.components_num,
						_type,
						_layout.attrib_size,
						ATTRIBUTE_OFFSET(_offset));
				}
				else if (_type == GL_HALF_FLOAT || _type == GL_FLOAT || _type == GL_FIXED)
				{
					glVertexAttribPointer(i, // vertex index  
						_layout.components_num, // num of attrib components
						_layout.components_type_enum, GL_FALSE, // type of attrib components
						_layout.attrib_size, // attrib bytes size
						ATTRIBUTE_OFFSET(_offset)); // collection offset
				}
				else if (_type == GL_DOUBLE)
				{
					glVertexAttribLPointer(i,
						_layout.components_num,
						_type,
						_layout.attrib_size,
						ATTRIBUTE_OFFSET(_offset));
				}
				glVertexAttribDivisor(i, _layout.divisor);

				_offset += (_layout.attribs_num) * (_layout.attrib_size);

				glDisableVertexAttribArray(i);
			}

			_unbind_buffer(); unbind();
		}

#ifdef _DEBUG

		const std::size_t _size = _descriptor->get_layouts().size();
		for (std::size_t i = 0; i < _size; ++i)
		{
			std::cout <<"pointer [" <<i<<"] " << is_pointer_enabled(static_cast<std::uint32_t>(i)) << std::endl;
			std::cout << "attribute components num: " << get_attribute_components_num(static_cast<std::uint32_t>(i)) << std::endl;
			std::cout << "attribute components type: " << get_attribute_component_type(static_cast<std::uint32_t>(i)) << std::endl;
		}
#endif
	}



	void _fill()
	{

		GLuint _binding = 0;
		glBindVertexBuffer(_binding, _buffer->get_handle(), 0, sizeof(Vertex));

		glEnableVertexAttribArray(0);
		glVertexAttribFormat(0, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, position));
		glVertexAttribBinding(0, _binding);

		glEnableVertexAttribArray(1);
		glVertexAttribFormat(1, 3, GL_FLOAT, GL_FALSE, offsetof(Vertex, normal));
		glVertexAttribBinding(1, _binding);
		
		glEnableVertexAttribArray(2);
		glVertexAttribFormat(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, offsetof(Vertex, color));
		glVertexAttribBinding(2, _binding);


		glVertexBindingDivisor()
	}


	void _fill()
	{
#define ATTRIBUTE_OFFSET(OFFSET) (const void*)(OFFSET)

		if (_descriptor)
		{
			const auto _data_size = _descriptor->get_data_size();
			const auto& _layouts = _descriptor->get_layouts();
			{
				_buffer = std::make_shared<gl_buffer>();
				_buffer->allocate(_data_size);
				_buffer->fill(0, _data_size, _descriptor->get_data());
			}

			bind(); //_bind_buffer(); // bind vertex array && bind buffer

			glBindVertexBuffer(0, _buffer->get_handle(), 0, )

			const std::uint32_t _max_pointer_index_num = static_cast<std::uint32_t>(_layouts.size());
			std::size_t _offset = 0;

			for (std::uint32_t i = 0; i < _max_pointer_index_num; ++i)
			{
				const auto& _layout = _layouts[i];
				const auto _type = _layout.components_type_enum;

				glEnableVertexAttribArray(i); // enable
				// set pointer
				if (_type == GL_BYTE || _type == GL_UNSIGNED_BYTE ||
					_type == GL_SHORT || _type == GL_UNSIGNED_SHORT ||
					_type == GL_INT || _type == GL_UNSIGNED_INT)
				{
					glVertexAttribIPointer(i,
						_layout.components_num,
						_type,
						_layout.attrib_size,
						ATTRIBUTE_OFFSET(_offset));
				}
				else if (_type == GL_HALF_FLOAT || _type == GL_FLOAT || _type == GL_FIXED)
				{
					glVertexAttribPointer(i, // vertex index  
						_layout.components_num, // num of attrib components
						_layout.components_type_enum, GL_FALSE, // type of attrib components
						_layout.attrib_size, // attrib bytes size
						ATTRIBUTE_OFFSET(_offset)); // collection offset
				}
				else if (_type == GL_DOUBLE)
				{
					glVertexAttribLPointer(i,
						_layout.components_num,
						_type,
						_layout.attrib_size,
						ATTRIBUTE_OFFSET(_offset));
				}
				glVertexAttribDivisor(i, _layout.divisor);

				_offset += (_layout.attribs_num) * (_layout.attrib_size);

				glDisableVertexAttribArray(i);
			}

			_unbind_buffer(); unbind();
		}

#ifdef _DEBUG

		const std::size_t _size = _descriptor->get_layouts().size();
		for (std::size_t i = 0; i < _size; ++i)
		{
			std::cout << "pointer [" << i << "] " << is_pointer_enabled(static_cast<std::uint32_t>(i)) << std::endl;
			std::cout << "attribute components num: " << get_attribute_components_num(static_cast<std::uint32_t>(i)) << std::endl;
			std::cout << "attribute components type: " << get_attribute_component_type(static_cast<std::uint32_t>(i)) << std::endl;
		}
#endif
	}

public:
	// default false
	bool is_pointer_enabled(std::uint32_t index)
	{
		bind();
		GLint _is_enabled = GL_FALSE;
		glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &_is_enabled);
		unbind();
		return _is_enabled;
	}
	// default is 4
	std::uint32_t get_attribute_components_num(std::uint32_t index)
	{
		bind();
		GLint _num = 0;
		glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_SIZE, &_num);
		unbind();
		return _num;
	}
	// default is GL_FLOAT
	std::string get_attribute_component_type(std::uint32_t index)
	{
		bind();
		GLint _num = 0;
		glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_TYPE, &_num);
		unbind();

		switch (_num)
		{
		case GL_FLOAT: return "float";
		default: return "";
			break;
		}
	}

	void* get_mapped_data()
	{
		if (_buffer)
			return _buffer->map(gl_buffer_enum::access::READ_WRITE);
		return nullptr;
	}

	std::int32_t get_size()
	{
		return _buffer->get_size();
	}

private:

	std::shared_ptr<gl_vertex_array_descriptor> _descriptor;

	std::shared_ptr<gl_buffer> _buffer;

};

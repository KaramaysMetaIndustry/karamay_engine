#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer.h"
#include "graphics/variable/glsl_types.h"

#define attribute_offset(offset) (const GLvoid*)(offset * sizeof(GLfloat))


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
	std::uint8_t do_normalization;
	std::uint32_t divisor;

	gl_vertex_attribute_layout() :
		attribs_num(0),
		attrib_size(0),
		components_num(0),
		components_type_enum(0),
		do_normalization(false),
		divisor(0)
	{

	}
};

class gl_vertex_array_descriptor final
{
public:

	gl_vertex_array_descriptor()
	{

	}

	~gl_vertex_array_descriptor()
	{

	}

public:

	template<typename T>
	void add_attributes(const std::vector<T>& attributes)
	{
		// add this kind of attribs into _data
		const std::uint8_t* _tmp_data = (std::uint8_t*)attributes.data();
		const std::size_t _tmp_size = attributes.size() * sizeof(T);
		for (std::size_t i = 0; i < _tmp_size; ++i)
		{
			_data.push_back(_tmp_data[i]);
		}

		gl_vertex_attribute_layout _layout;
		_layout.components_num = T::length();
		_layout.components_type_enum = _get_component_type_enum<T::value_type>();
		_layout.attrib_size = sizeof(T);
		_layout.attribs_num = static_cast<std::uint32_t>(attributes.size());
		_layouts.push_back(_layout);

		_is_dirty = true;
	}

	template<>
	void add_attributes(const std::vector<glv_int>& attributes)
	{
		// add this kind of attribs into _data
		const std::uint8_t* _tmp_data = (std::uint8_t*)attributes.data();
		const std::size_t _tmp_size = attributes.size() * sizeof(glv_int);
		for (std::size_t i = 0; i < _tmp_size; ++i) { _data.push_back(_tmp_data[i]); }

		gl_vertex_attribute_layout _layout;
		_layout.components_num = 1;
		_layout.components_type_enum = _get_component_type_enum<glv_int>();
		_layout.attrib_size = sizeof(glv_int);
		_layout.attribs_num = static_cast<std::uint32_t>(attributes.size());
		_layouts.push_back(_layout);

		_is_dirty = true;
	}

	template<>
	void add_attributes(const std::vector<glv_uint>& attributes)
	{
		// add this kind of attribs into _data
		const std::uint8_t* _tmp_data = (std::uint8_t*)attributes.data();
		const std::size_t _tmp_size = attributes.size() * sizeof(glv_uint);
		for (std::size_t i = 0; i < _tmp_size; ++i) { _data.push_back(_tmp_data[i]); }

		gl_vertex_attribute_layout _layout;
		_layout.components_num = 1;
		_layout.components_type_enum = _get_component_type_enum<glv_uint>();
		_layout.attrib_size = sizeof(glv_uint);
		_layout.attribs_num = static_cast<std::uint32_t>(attributes.size());
		_layouts.push_back(_layout);

		_is_dirty = true;
	}

	template<>
	void add_attributes(const std::vector<glv_float>& attributes)
	{
		// add this kind of attribs into _data
		const std::uint8_t* _tmp_data = (std::uint8_t*)attributes.data();
		const std::size_t _tmp_size = attributes.size() * sizeof(glv_float);
		for (std::size_t i = 0; i < _tmp_size; ++i) { _data.push_back(_tmp_data[i]); }

		gl_vertex_attribute_layout _layout;
		_layout.components_num = 1;
		_layout.components_type_enum = _get_component_type_enum<glv_float>();
		_layout.attrib_size = sizeof(glv_float);
		_layout.attribs_num = static_cast<std::uint32_t>(attributes.size());
		_layouts.push_back(_layout);

		_is_dirty = true;
	}

	template<>
	void add_attributes(const std::vector<glv_double>& attributes)
	{
		// add this kind of attribs into _data
		const std::uint8_t* _tmp_data = (std::uint8_t*)attributes.data();
		const std::size_t _tmp_size = attributes.size() * sizeof(glv_double);
		for (std::size_t i = 0; i < _tmp_size; ++i) { _data.push_back(_tmp_data[i]); }

		gl_vertex_attribute_layout _layout;
		_layout.components_num = 1;
		_layout.components_type_enum = _get_component_type_enum<glv_double>();
		_layout.attrib_size = sizeof(glv_double);
		_layout.attribs_num = static_cast<std::uint32_t>(attributes.size());
		_layouts.push_back(_layout);

		_is_dirty = true;
	}


private:

	template<typename T>
	inline std::uint32_t _get_component_type_enum() { return 0; }
	template<>
	inline std::uint32_t _get_component_type_enum<glv_int>() { return GL_INT; }
	template<>
	inline std::uint32_t _get_component_type_enum<glv_uint>() { return GL_UNSIGNED_INT; }
	template<>
	inline std::uint32_t _get_component_type_enum<glv_float>() { return GL_FLOAT; }
	template<>
	inline std::uint32_t _get_component_type_enum<glv_double>() { return GL_DOUBLE; }
	
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


class gl_vertex_array : public gl_object
{
public:

	gl_vertex_array();

	virtual ~gl_vertex_array();

public:

	void fill(std::shared_ptr<gl_vertex_array_descriptor> descriptor);

public:

	void tick(std::float_t delta_time);

	void bind();

	void unbind();

	void enable_pointers();

	void disable_pointers();

private:

	inline void _bind_array_buffer()
	{
		if (_buffer)
			glBindBuffer(GL_ARRAY_BUFFER, _buffer->get_handle());
	}

	inline void _unbind_array_buffer()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void _fill()
	{
#define ATTRIBUTE_OFFSET(offset) (const GLvoid*)(offset * sizeof(GLfloat))

		if (_descriptor)
		{
			const size_t _packed_data_size = _descriptor->get_data_size();
			const std::vector<gl_vertex_attribute_layout>& _layouts = _descriptor->get_layouts();
			{
				_buffer = std::make_shared<gl_buffer>();
				_buffer->allocate(_packed_data_size);
				_buffer->fill(0, _packed_data_size, _descriptor->get_data());
			}

			bind(); _bind_array_buffer();
			
			std::uint32_t _offset = 0;

			for (std::uint32_t i = 0; i < _layouts.size(); ++i)
			{
				const auto& _layout = _layouts[i];
				const std::uint32_t _type = _layout.components_type_enum;
				
				// enable index
				glEnableVertexAttribArray(i);
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
						_layouts[i].components_num, // num of attrib components
						_layouts[i].components_type_enum, GL_FALSE, // type of attrib components
						_layouts[i].attrib_size, // attrib bytes size
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
				//glVertexAttribDivisor(i, 3);

				_offset += _layouts[i].attribs_num * _layouts[i].attrib_size;

				glDisableVertexAttribArray(i);
			}

			this->unbind(); // unbind vertex array
			_unbind_array_buffer(); // unbind buffer
		}


#ifdef _DEBUG

		const std::size_t _size = _descriptor->get_layouts().size();
		for (std::size_t i = 0; i < _size; ++i)
		{
			std::cout <<"pointer [" <<i<<"] " << is_pointer_enabled(i) << std::endl;
			std::cout << "attribute components num: " << get_attribute_components_num(i) << std::endl;
			std::cout << "attribute components type: " << get_attribute_component_type(i) << std::endl;
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


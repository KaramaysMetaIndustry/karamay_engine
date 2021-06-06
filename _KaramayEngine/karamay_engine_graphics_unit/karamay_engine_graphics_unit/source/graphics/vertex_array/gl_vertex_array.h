#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer.h"
#include "graphics/variable/glv_types.h"

namespace gl_vertex_array_enum
{
	enum class attribute_component_type
	{
		BYTE = GL_BYTE, // GLbyte
		UNSIGNED_BYTE = GL_UNSIGNED_BYTE, // GLubyte
		SHORT = GL_SHORT, // GLshort
		UNSIGNED_SHORT = GL_UNSIGNED_SHORT, // GLushort
		INT = GL_INT, // GLint
		UNSIGNED_INT = GL_UNSIGNED_INT, // GLuint

		HALF_FLOAT = GL_HALF_FLOAT, // GLhalf
		FLOAT = GL_FLOAT, // GLfloat
		FIXED = GL_FIXED, // GLfixed
		INT_2_10_10_10_REV = GL_INT_2_10_10_10_REV,
		UNSIGNED_INT_2_10_10_10_REV = GL_UNSIGNED_INT_2_10_10_10_REV,
		UNSIGNED_INT_10F_11F_11F_REV = GL_UNSIGNED_INT_10F_11F_11F_REV,

		DOUBLE = GL_DOUBLE, // GLdouble
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
	void add_attributes(const std::vector<T>& attributes, std::uint32_t divisor = 0)
	{
		{
			static_assert(
				std::is_same<glv_i8vec1, T>::value ||
				std::is_same<glv_i8vec2, T>::value ||
				std::is_same<glv_i8vec3, T>::value ||
				std::is_same<glv_i8vec4, T>::value || // int8
				std::is_same<glv_i16vec4, T>::value ||
				std::is_same<glv_i16vec1, T>::value ||
				std::is_same<glv_i16vec2, T>::value ||
				std::is_same<glv_i16vec3, T>::value ||
				std::is_same<glv_i16vec4, T>::value || // int16
				std::is_same<glv_i32vec4, T>::value ||
				std::is_same<glv_i32vec1, T>::value ||
				std::is_same<glv_i32vec2, T>::value ||
				std::is_same<glv_i32vec3, T>::value ||
				std::is_same<glv_i32vec4, T>::value || // int32
				std::is_same<glv_ui8vec1, T>::value ||
				std::is_same<glv_ui8vec2, T>::value ||
				std::is_same<glv_ui8vec3, T>::value ||
				std::is_same<glv_ui8vec4, T>::value || // uint8
				std::is_same<glv_ui8vec1, T>::value ||
				std::is_same<glv_ui8vec2, T>::value ||
				std::is_same<glv_ui8vec3, T>::value ||
				std::is_same<glv_ui8vec4, T>::value || // uint16
				std::is_same<glv_ui8vec1, T>::value ||
				std::is_same<glv_ui8vec2, T>::value ||
				std::is_same<glv_ui8vec3, T>::value ||
				std::is_same<glv_ui8vec4, T>::value || // uint32
				std::is_same<glv_f32vec1, T>::value ||
				std::is_same<glv_f32vec2, T>::value ||
				std::is_same<glv_f32vec3, T>::value ||
				std::is_same<glv_f32vec4, T>::value || // float
				std::is_same<glv_f64vec1, T>::value ||
				std::is_same<glv_f64vec2, T>::value ||
				std::is_same<glv_f64vec3, T>::value ||
				std::is_same<glv_f64vec4, T>::value || // double
				std::is_same<glv_f32mat2, T>::value ||
				std::is_same<glv_f32mat2x3, T>::value ||
				std::is_same<glv_f32mat2x4, T>::value ||
				std::is_same<glv_f32mat3, T>::value ||
				std::is_same<glv_f32mat3x2, T>::value ||
				std::is_same<glv_f32mat3x4, T>::value ||
				std::is_same<glv_f32mat4, T>::value ||
				std::is_same<glv_f32mat4x2, T>::value ||
				std::is_same<glv_f32mat4x3, T>::value || // float mat
				std::is_same<glv_f64mat2, T>::value ||
				std::is_same<glv_f64mat2x3, T>::value ||
				std::is_same<glv_f64mat2x4, T>::value ||
				std::is_same<glv_f64mat3, T>::value ||
				std::is_same<glv_f64mat3x2, T>::value ||
				std::is_same<glv_f64mat3x4, T>::value ||
				std::is_same<glv_f64mat4, T>::value ||
				std::is_same<glv_f64mat4x2, T>::value ||
				std::is_same<glv_f64mat4x3, T>::value    // double mat
				, "T must be glv_* types.");
		}
		
		const std::uint8_t* _bytes = (const std::uint8_t*)(attributes.data());
		const std::size_t _bytes_num = attributes.size() * sizeof(T);

		// prevent calling reallocating many times
		_stream.reserve(_bytes_num);
		for (std::size_t _index = 0; _index < _bytes_num; _stream.push_back(_bytes[_index]), ++_index) {}
		
		// describe attribues layout
		gl_vertex_attribute_layout _layout;
		_layout.components_num = T::length();
		_layout.components_type_enum = _get_component_type_enum<T::value_type>();
		_layout.attrib_size = sizeof(T);
		_layout.attribs_num = static_cast<std::uint32_t>(attributes.size());
		_layout.normalized = false;
		_layout.divisor = divisor;
		_layouts.push_back(_layout);

		_is_dirty = true;
	}

	template<typename T>
	void add_normalized_attributes(const std::vector<T>& attributes, std::uint32_t divisor = 0)
	{
		{
			static_assert(
				std::is_same<glv_i8vec1, T>::value ||
				std::is_same<glv_i8vec2, T>::value ||
				std::is_same<glv_i8vec3, T>::value ||
				std::is_same<glv_i8vec4, T>::value || // int8
				std::is_same<glv_i16vec4, T>::value ||
				std::is_same<glv_i16vec1, T>::value ||
				std::is_same<glv_i16vec2, T>::value ||
				std::is_same<glv_i16vec3, T>::value ||
				std::is_same<glv_i16vec4, T>::value || // int16
				std::is_same<glv_i32vec4, T>::value ||
				std::is_same<glv_i32vec1, T>::value ||
				std::is_same<glv_i32vec2, T>::value ||
				std::is_same<glv_i32vec3, T>::value ||
				std::is_same<glv_i32vec4, T>::value || // int32
				std::is_same<glv_ui8vec1, T>::value ||
				std::is_same<glv_ui8vec2, T>::value ||
				std::is_same<glv_ui8vec3, T>::value ||
				std::is_same<glv_ui8vec4, T>::value || // uint8
				std::is_same<glv_ui8vec1, T>::value ||
				std::is_same<glv_ui8vec2, T>::value ||
				std::is_same<glv_ui8vec3, T>::value ||
				std::is_same<glv_ui8vec4, T>::value || // uint16
				std::is_same<glv_ui8vec1, T>::value ||
				std::is_same<glv_ui8vec2, T>::value ||
				std::is_same<glv_ui8vec3, T>::value ||
				std::is_same<glv_ui8vec4, T>::value  // uint32
				, "T must be glv_i* or glv_ui* types.");
		}
		
		const std::uint8_t* _bytes = (const std::uint8_t*)(attributes.data());
		const std::size_t _bytes_num = attributes.size() * sizeof(T);

		// prevent calling reallocating many times
		_stream.reserve(_bytes_num);
		for (std::size_t _index = 0; _index < _bytes_num; _stream.push_back(_bytes[_index]), ++_index) {}

		// describe attribues layout
		gl_vertex_attribute_layout _layout;
		_layout.components_num = T::length();
		_layout.components_type_enum = _get_component_type_enum<T::value_type>();
		_layout.attrib_size = sizeof(T);
		_layout.attribs_num = static_cast<std::uint32_t>(attributes.size());
		_layout.normalized = true;
		_layout.divisor = divisor;
		_layouts.push_back(_layout);

		_is_dirty = true;
	}

public:

	const void* get_stream() const;

	const std::size_t get_stream_size() const;

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

	std::vector<std::uint8_t> _stream;

	std::vector<gl_vertex_attribute_layout> _layouts;

	std::uint8_t _is_dirty : 1;

private:

	template<typename T>
	inline std::uint32_t _get_component_type_enum() { return 0; }
	
	template<>
	inline std::uint32_t _get_component_type_enum<glv_i8vec1::value_type>() { return GL_BYTE; }
	
	template<>
	inline std::uint32_t _get_component_type_enum<glv_ui8vec1::value_type>() { return GL_UNSIGNED_BYTE; }
	
	template<>
	inline std::uint32_t _get_component_type_enum<glv_i16vec1::value_type>() { return GL_SHORT; }
	
	template<>
	inline std::uint32_t _get_component_type_enum<glv_ui16vec1::value_type>() { return GL_UNSIGNED_SHORT; }
	
	template<>
	inline std::uint32_t _get_component_type_enum<glv_i32vec1::value_type>() { return GL_INT; }
	
	template<>
	inline std::uint32_t _get_component_type_enum<glv_ui32vec1::value_type>() { return GL_UNSIGNED_INT; }
	
	template<>
	inline std::uint32_t _get_component_type_enum<glv_f32vec1::value_type>() { return GL_FLOAT; }
	
	template<>
	inline std::uint32_t _get_component_type_enum<glv_f64vec1::value_type>() { return GL_DOUBLE; }
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

	~gl_vertex_array();

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
		if (_descriptor)
		{
			const auto _stream_size = _descriptor->get_stream_size();
			_buffer = std::make_shared<gl_buffer>();
			_buffer->allocate(_stream_size);
			_buffer->fill(0, _stream_size, _descriptor->get_stream());

			bind(); _bind_buffer();

			const auto& _layouts = _descriptor->get_layouts();
			const std::uint32_t _max_index_num = static_cast<std::uint32_t>(_layouts.size());
			std::size_t _offset = 0;

			for (std::uint32_t _index = 0; _index < _max_index_num; ++_index)
			{
				const auto& _layout = _layouts[_index];
				const auto _normalized = _layout.normalized;
				
				const auto _component_type_enum = _layout.components_type_enum;
				const auto _components_num = _layout.components_num;
				const auto _attribute_size = _layout.attrib_size;
				const auto _attributes_num = _layout.attribs_num;

				const auto _divisor = _layout.divisor;
				
				if (_normalized) // integers -> normalized floats
				{
					if (_component_type_enum == GL_BYTE || _component_type_enum == GL_UNSIGNED_BYTE ||
						_component_type_enum == GL_SHORT || _component_type_enum == GL_UNSIGNED_SHORT ||
						_component_type_enum == GL_INT || _component_type_enum == GL_UNSIGNED_INT)
					{
						glVertexAttribPointer(_index,
							_components_num,
							_component_type_enum, GL_TRUE,
							_attribute_size,
							reinterpret_cast<const void*>(_offset));
					}
				}
				else { // original integers
					if (_component_type_enum == GL_BYTE || _component_type_enum == GL_UNSIGNED_BYTE ||
						_component_type_enum == GL_SHORT || _component_type_enum == GL_UNSIGNED_SHORT ||
						_component_type_enum == GL_INT || _component_type_enum == GL_UNSIGNED_INT)
					{
						glVertexAttribIPointer(_index,
							_components_num,
							_component_type_enum,
							_attribute_size,
							reinterpret_cast<const void*>(_offset));
					} 
					else if (_component_type_enum == GL_HALF_FLOAT || _component_type_enum == GL_FLOAT ||
						_component_type_enum == GL_FIXED) // original floats
					{
						glVertexAttribPointer(_index, 
							_components_num, 
							_component_type_enum, GL_FALSE,
							_attribute_size,
							reinterpret_cast<const void*>(_offset));
					}
					else if (_component_type_enum == GL_DOUBLE) // original doubles
					{
						glVertexAttribLPointer(_index,
							_components_num,
							_component_type_enum,
							_attribute_size,
							reinterpret_cast<const void*>(_offset));
					}
				}

				glVertexAttribDivisor(_index, _divisor);

				_offset += static_cast<std::size_t>(_attributes_num) * _attribute_size;
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
		case GL_BYTE: return "BYTE";
		case GL_UNSIGNED_BYTE: return "UNSIGNED BYTE";
		case GL_SHORT: return "SHORT";
		case GL_UNSIGNED_SHORT: return "UNSIGNED SHORT";
		case GL_INT: return "INT";
		case GL_UNSIGNED_INT: return "UNSIGNED INT";
		case GL_FLOAT: return "FLOAT";
		case GL_DOUBLE: return "DOUBLE";
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

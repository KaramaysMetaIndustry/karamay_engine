#ifndef H_GL_VERTEX_ARRAY
#define H_GL_VERTEX_ARRAY

#include "graphics/glo/gl_object.h"
#include "graphics/variable/glv_types.h"


class gl_buffer;

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

	gl_vertex_array(std::shared_ptr<gl_vertex_array_descriptor> descriptor);

private:

	std::shared_ptr<gl_vertex_array_descriptor> _descriptor;

	std::shared_ptr<gl_buffer> _buffer;

public:

	void bind();

	void unbind();

	void enable_pointers();

	void disable_pointers();

private:

	void _bind_buffer();

	void _unbind_buffer();

	void _fill();

public:
	// default false
	bool is_pointer_enabled(std::uint32_t index);
	// default is 4
	std::uint32_t get_attribute_components_num(std::uint32_t index);
	// default is GL_FLOAT
	std::string get_attribute_component_type(std::uint32_t index);

	void* get_mapped_data();

	const std::int32_t get_size() const;

public:
	
	~gl_vertex_array();

};

#endif

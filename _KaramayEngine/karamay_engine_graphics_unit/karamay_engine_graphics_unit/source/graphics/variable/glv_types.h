#pragma once
#include "public/opengl.h"
// transparent types


// highp meduimp lowp

// GL_FLOAT float
using glv_f32vec1 = glm::f32vec1;
using glv_f32vec2 = glm::f32vec2;
using glv_f32vec3 = glm::f32vec3;
using glv_f32vec4 = glm::f32vec4; 

// GL_DOUBLE double
using glv_f64vec1 = glm::f64vec1;
using glv_f64vec2 = glm::f64vec2;
using glv_f64vec3 = glm::f64vec3;
using glv_f64vec4 = glm::f64vec4; 

// GL_BYTE -> bool/int
using glv_i8vec1 = glm::i8vec1;
using glv_i8vec2 = glm::i8vec2;
using glv_i8vec3 = glm::i8vec3;
using glv_i8vec4 = glm::i8vec4; 

// GL_SHORT -> int
using glv_i16vec1 = glm::i16vec1;
using glv_i16vec2 = glm::i16vec2;
using glv_i16vec3 = glm::i16vec3;
using glv_i16vec4 = glm::i16vec4;

// GL_INT -> int
using glv_i32vec1 = glm::i32vec1;
using glv_i32vec2 = glm::i32vec2;
using glv_i32vec3 = glm::i32vec3;
using glv_i32vec4 = glm::i32vec4;

// GL_UNSIGNED_BYTE -> uint
using glv_ui8vec1 = glm::u8vec1;
using glv_ui8vec2 = glm::u8vec2;
using glv_ui8vec3 = glm::u8vec3;
using glv_ui8vec4 = glm::u8vec4;

// GL_UNSIGNED_SHORT -> uint
using glv_ui16vec1 = glm::u16vec1;
using glv_ui16vec2 = glm::u16vec2;
using glv_ui16vec3 = glm::u16vec3;
using glv_ui16vec4 = glm::u16vec4;

// GL_UNSIGNED_INT -> uint
using glv_ui32vec1 = glm::u32vec1;
using glv_ui32vec2 = glm::u32vec2;
using glv_ui32vec3 = glm::u32vec3;
using glv_ui32vec4 = glm::u32vec4;


using glv_f32mat2 = glm::mat2;
using glv_f32mat2x3 = glm::mat2x3;
using glv_f32mat2x4 = glm::mat2x4;
using glv_f32mat3 = glm::mat3;
using glv_f32mat3x2 = glm::mat3x2;
using glv_f32mat3x4 = glm::mat3x4;
using glv_f32mat4 = glm::mat4;
using glv_f32mat4x2 = glm::mat4x2;
using glv_f32mat4x3 = glm::mat4x3;
using glv_f64mat2 = glm::dmat2;
using glv_f64mat2x3 = glm::dmat2x3;
using glv_f64mat2x4 = glm::dmat2x4;
using glv_f64mat3 = glm::dmat3;
using glv_f64mat3x2 = glm::dmat3x2;
using glv_f64mat3x4 = glm::dmat3x4;
using glv_f64mat4 = glm::dmat4;
using glv_f64mat4x2 = glm::dmat4x2;
using glv_f64mat4x3 = glm::dmat4x3;



template<typename T>
class vertex_attribute_stream
{
public:

	vertex_attribute_stream(const std::vector<T>& stream)
	{
		_stream = stream;
	}


private:

	std::vector<std::uint8_t> _stream;

public:

	const void* get_stream_bytes() const
	{
		return _stream.data();
	}

	const size_t get_stream_size() const
	{
		return _stream.size();
	}

};

template<typename T>
class normalizable_vertex_attribute_stream
{
public:

	normalizable_vertex_attribute_stream(const std::vector<T>& stream, bool normalized)
	{
		_stream = stream;
	}
};
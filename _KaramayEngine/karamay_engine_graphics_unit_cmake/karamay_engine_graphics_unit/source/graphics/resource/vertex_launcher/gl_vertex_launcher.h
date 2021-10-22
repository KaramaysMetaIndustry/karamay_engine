#ifndef GL_VERTEX_LAUNCHER_H
#define GL_VERTEX_LAUNCHER_H

#include "graphics/resource/vertex_array/gl_vertex_array.h"
#include "graphics/resource/buffers/common_buffer/gl_element_array_buffer.h"

enum class gl_primitive
{
	POINTS = GL_POINTS,

	LINES = GL_LINES,
	LINES_ADJACENCY = GL_LINES_ADJACENCY,
	LINE_LOOP = GL_LINE_LOOP,
	LINE_STRIP_ADJACENCY = GL_LINE_STRIP_ADJACENCY,
	LINE_STRIP = GL_LINE_STRIP,

	TRIANGLES = GL_TRIANGLES,
	TRIANGLES_ADJACENCY = GL_TRIANGLES_ADJACENCY,
	TRIANGLE_STRIP = GL_TRIANGLE_STRIP,
	TRIANGLE_STRIP_ADJACENCY = GL_TRIANGLE_STRIP_ADJACENCY,
	TRIANGLE_FAN = GL_TRIANGLE_FAN,
	
	PATCHES = GL_PATCHES
};

struct gl_primitive_mode
{

};


class gl_vertex_launcher final{
public:
	gl_vertex_launcher(std::uint32_t primitives_num) 
	{
		_element_array_buffer = std::make_unique<gl_element_array_buffer>(primitives_num * 3);
	}

	~gl_vertex_launcher() {}

private:

	std::unique_ptr<gl_vertex_array> _vertex_array;

	std::unique_ptr<gl_element_array_buffer> _element_array_buffer;

public:

	void bind() noexcept
	{
		if (!_vertex_array || !_element_array_buffer) return;

		_vertex_array->bind();
		_element_array_buffer->bind();
	}

	void unbind() noexcept
	{
		if (!_vertex_array || !_element_array_buffer) return;

		_vertex_array->unbind();
		_element_array_buffer->unbind();
	}

};


#endif
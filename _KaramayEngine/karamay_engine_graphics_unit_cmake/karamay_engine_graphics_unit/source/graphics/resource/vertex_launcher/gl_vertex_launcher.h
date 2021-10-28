#ifndef GL_VERTEX_LAUNCHER_H
#define GL_VERTEX_LAUNCHER_H

#include "graphics/resource/vertex_array/gl_vertex_array.h"
#include "graphics/resource/buffers/common_buffer/gl_element_array_buffer.h"

enum class gl_primitive_mode
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


class gl_vertex_launcher final{
public:
	gl_vertex_launcher() :
		vertices(nullptr), indices(nullptr)
	{}

	gl_vertex_launcher(const gl_vertex_launcher&) = delete;
	gl_vertex_launcher& operator=(const gl_vertex_launcher&) = delete;

	~gl_vertex_launcher() = default;

public:

	std::shared_ptr<gl_vertex_array> vertices;

	std::shared_ptr<gl_element_array_buffer> indices;

	gl_primitive_mode primitive_mode;

public:

	bool assembly() noexcept
	{
		return false;
	}

	void bind() noexcept
	{
		if(vertices) vertices->bind();
		if(indices) indices->bind();
	}

	void unbind() noexcept
	{
		if(vertices) vertices->unbind();
		if(indices) indices->unbind();
	}

};


#endif
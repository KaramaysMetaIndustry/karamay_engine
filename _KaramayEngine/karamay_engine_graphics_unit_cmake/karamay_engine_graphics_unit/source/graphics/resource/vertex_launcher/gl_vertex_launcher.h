#ifndef GL_VERTEX_LAUNCHER_H
#define GL_VERTEX_LAUNCHER_H

#include "graphics/resource/vertex_array/gl_vertex_array.h"
#include "graphics/resource/buffers/common_buffer/gl_element_array_buffer.h"

class gl_vertex_launcher final{
public:
	gl_vertex_launcher() :
		vertices(nullptr),
		indices(nullptr)
	{}

	~gl_vertex_launcher() = default;

public:

	std::shared_ptr<gl_vertex_array> vertices;

	std::shared_ptr<gl_element_array_buffer> indices;

	bool assembly()
	{
		return false;
	}

	void bind() noexcept
	{
		if (!vertices || !indices) return;

		vertices->bind();
		indices->bind();
	}

	void unbind() noexcept
	{
		if (!vertices || !indices) return;

		vertices->unbind();
		indices->unbind();
	}

};


#endif
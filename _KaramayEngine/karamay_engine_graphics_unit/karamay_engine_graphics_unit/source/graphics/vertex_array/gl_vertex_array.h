#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer.h"

#define attribute_offset(offset) (const GLvoid*)(offset * sizeof(GLfloat))


namespace gl_vertex_array_enum
{

}


struct gl_vertex_attribute_layout
{
	std::uint32_t index;
	std::uint32_t size; 
	GLenum type; 
	std::uint32_t offset;
	std::uint32_t divisor;

	gl_vertex_attribute_layout(std::uint32_t index, std::uint32_t size, GLenum type, std::uint32_t offset) {}
};

class gl_vertex_array : public gl_object
{
public:

	gl_vertex_array();

	virtual ~gl_vertex_array();

private:

	std::shared_ptr<gl_buffer> _ref_buffer;

	std::vector<std::uint32_t> _indices;

public:
	
	void fill(const void* data, std::size_t size, const std::vector<gl_vertex_attribute_layout>& layouts);

public:
	
	void bind()
	{
		glBindVertexArray(_handle);
	}

	void unbind()
	{
		glBindVertexArray(0);
	}

	void enable_vertex_attributes();

	void disable_vertex_attributes();

};


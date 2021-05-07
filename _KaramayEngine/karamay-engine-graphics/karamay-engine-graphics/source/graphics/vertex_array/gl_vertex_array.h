#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer.h"

class gl_buffer;

#define attribute_offset(offset) (const GLvoid*)(offset * sizeof(GLfloat))


struct gl_vertex_attribute_pointer
{
	std::uint32_t index;
	GLint size; 
	GLenum type; 
	GLuint offset;
};

class gl_vertex_array : public gl_object
{
public:

	gl_vertex_array()
	{
		glCreateVertexArrays(1, &_handle);
	}

	virtual ~gl_vertex_array()
	{
		glDeleteVertexArrays(1, &_handle);
	}

private:

	std::vector<std::uint32_t> indices;


public:

	void set_array_buffer(std::shared_ptr<gl_buffer> array_buffer, const gl_vertex_attribute_pointer& pointer);

	void set_array_buffer(std::shared_ptr<gl_buffer> array_buffer, const std::vector<gl_vertex_attribute_pointer>& pointers);

	void set_element_array_buffer(std::shared_ptr<gl_buffer> element_array_buffer);

public:
	
	void bind();

	void unbind();

	void enable_vertex_attributes();

	void disable_vertex_attributes();

};


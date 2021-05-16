#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer.h"

#define attribute_offset(offset) (const GLvoid*)(offset * sizeof(GLfloat))


namespace gl_vertex_array_enum
{

}


struct gl_vertex_attribute_pointer
{
	std::uint32_t index;
	std::uint32_t size; 
	GLenum type; 
	std::uint32_t offset;

	gl_vertex_attribute_pointer(std::uint32_t index, std::uint32_t size, GLenum type, std::uint32_t offset) {}
};

struct gl_vertex_attribute_pointer_instanced
{
	std::uint32_t index;
	std::uint32_t size;
	GLenum type;
	std::uint32_t offset;
	std::uint32_t divisor;
};

class gl_vertex_array : public gl_object
{
public:

	gl_vertex_array();

	virtual ~gl_vertex_array();

private:

	std::shared_ptr<gl_buffer> _ref_buffer;

	std::uint32_t _offset, _size;


	std::vector<std::uint32_t> indices;

public:
	
	void fill(const void* data, const std::vector<gl_vertex_attribute_pointer>& pointers)
	{
		_ref_buffer->fill(_offset, _size, data);

	}


	void associate_array_buffer(std::shared_ptr<gl_buffer> array_buffer, const std::vector<gl_vertex_attribute_pointer>& pointers);

	void associate_array_buffer_instanced(std::shared_ptr<gl_buffer> array_buffer, const std::vector<gl_vertex_attribute_pointer_instanced>& pointers);

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


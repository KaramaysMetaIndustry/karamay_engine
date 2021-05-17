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

	gl_vertex_attribute_layout(std::uint32_t index, std::uint32_t size, GLenum type, std::uint32_t offset) {}
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

	std::vector<std::uint32_t> _indices;

public:
	
	void fill(const void* data, std::size_t size, const std::vector<gl_vertex_attribute_layout>& layouts)
	{
		_ref_buffer = std::make_shared<gl_buffer>();
		_ref_buffer->allocate(size);
		_ref_buffer->fill(0, size, data);

		bind();
		_ref_buffer->bind();
		for (const auto& layout : layouts)
		{
			glEnableVertexAttribArray(static_cast<GLuint>(layout.index));
			glVertexAttribPointer(static_cast<GLuint>(layout.index), static_cast<GLintptr>(layout.size), static_cast<GLenum>(layout.type), GL_FALSE, sizeof(GLfloat) * layout.size, attribute_offset(layout.offset));
			_indices.push_back(layout.index);
		}
		_ref_buffer->unbind();
		unbind();
	}

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


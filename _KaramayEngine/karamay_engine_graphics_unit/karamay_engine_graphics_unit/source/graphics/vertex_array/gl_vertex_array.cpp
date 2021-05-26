#include "gl_vertex_array.h"

gl_vertex_array::gl_vertex_array()
{
	glCreateVertexArrays(1, &_handle);
}

gl_vertex_array::~gl_vertex_array()
{
	glDeleteVertexArrays(1, &_handle);
}

void gl_vertex_array::_fill()
{
	const size_t size = _descriptor->size;
	const void* data = _descriptor->data;
	const auto& layouts = _descriptor->layouts;

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

void gl_vertex_array::enable_vertex_attributes()
{
	for (const auto index : _indices)
	{
		glEnableVertexAttribArray(static_cast<GLuint>(index));
	}
}

void gl_vertex_array::disable_vertex_attributes()
{
	for (const auto index : _indices)
	{
		glDisableVertexAttribArray(static_cast<GLuint>(index));
	}
}

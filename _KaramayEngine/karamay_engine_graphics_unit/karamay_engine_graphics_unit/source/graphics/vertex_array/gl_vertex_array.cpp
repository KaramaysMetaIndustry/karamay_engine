#include "gl_vertex_array.h"

gl_vertex_array::gl_vertex_array()
{
	glCreateVertexArrays(1, &_handle);
}

gl_vertex_array::~gl_vertex_array()
{
	glDeleteVertexArrays(1, &_handle);
}

void gl_vertex_array::associate_array_buffer(std::shared_ptr<gl_buffer> array_buffer, const std::vector<gl_vertex_attribute_pointer>& pointers)
{
	//if (array_buffer && array_buffer->is(gl_buffer_enum::type::ARRAY_BUFFER))
	//{
	//	bind();
	//	array_buffer->bind();
	//	for (const auto& pointer : pointers)
	//	{	// set pointer
	//		glEnableVertexAttribArray(static_cast<GLuint>(pointer.index));
	//		glVertexAttribPointer(static_cast<GLuint>(pointer.index), static_cast<GLint>(pointer.size), static_cast<GLenum>(pointer.type), GL_FALSE, sizeof(GLfloat) * pointer.size, attribute_offset(pointer.offset));
	//		indices.push_back(pointer.index);
	//	}
	//	array_buffer->unbind(); // glVertexAttribPointer has stored the buffer's handle, unbind will not affect anything, unless the buffer object has been destroyed
	//	unbind();
	//}
}

void gl_vertex_array::associate_array_buffer_instanced(std::shared_ptr<gl_buffer> array_buffer, const std::vector<gl_vertex_attribute_pointer_instanced>& pointers)
{
	//if (array_buffer)
	//{
	//	bind();
	//	array_buffer->bind();
	//	for (const auto& pointer : pointers)
	//	{	// set pointer
	//		glEnableVertexAttribArray(static_cast<GLuint>(pointer.index));
	//		glVertexAttribPointer(static_cast<GLuint>(pointer.index), static_cast<GLint>(pointer.size), static_cast<GLenum>(pointer.type), GL_FALSE, sizeof(GLfloat) * pointer.size, attribute_offset(pointer.offset));
	//		glVertexAttribDivisor(static_cast<GLuint>(pointer.index), static_cast<GLuint>(pointer.divisor));
	//		indices.push_back(pointer.index);
	//	}
	//	array_buffer->unbind();
	//	unbind();
	//}
}

void gl_vertex_array::enable_vertex_attributes()
{
	for (const auto index : indices)
	{
		glEnableVertexAttribArray(static_cast<GLuint>(index));
	}
}

void gl_vertex_array::disable_vertex_attributes()
{
	for (const auto index : indices)
	{
		glDisableVertexAttribArray(static_cast<GLuint>(index));
	}
}

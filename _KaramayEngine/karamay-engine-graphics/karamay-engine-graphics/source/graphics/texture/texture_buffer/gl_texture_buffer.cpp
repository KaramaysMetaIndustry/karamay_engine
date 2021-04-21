#include "gl_texture_buffer.h"

void gl_texture_buffer::associate_buffer(GLenum internal_format, GLuint buffer_handle)
{
	glTexBuffer(GL_TEXTURE_BUFFER, internal_format, buffer_handle);
}

void gl_texture_buffer::associate_sub_buffer(GLenum internal_format, GLuint buffer_handle, GLintptr offset, GLsizeiptr size)
{
	glTexBufferRange(GL_TEXTURE_BUFFER, internal_format, buffer_handle, offset, size);
}

void gl_texture_buffer::bind(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_BUFFER, _handle);
}

void gl_texture_buffer::unbind()
{
}

gl_texture_buffer::gl_texture_buffer()
{
}

gl_texture_buffer::~gl_texture_buffer()
{
}

#include "gl_texture_buffer.h"

void gl_texture_buffer::associate_sub_buffer(GLenum internal_format, GLuint buffer_handle, GLintptr offset, GLsizeiptr size)
{
	glTexBufferRange(GL_TEXTURE_BUFFER, internal_format, buffer_handle, offset, size);
}

void gl_texture_buffer::bind(std::uint32_t unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_BUFFER, _handle);
}

void gl_texture_buffer::unbind()
{
}

gl_texture_buffer::gl_texture_buffer()
{
	glCreateTextures(GL_TEXTURE_BUFFER, 1, &_handle);
}

gl_texture_buffer::~gl_texture_buffer()
{
	glDeleteTextures(1, &_handle);
}

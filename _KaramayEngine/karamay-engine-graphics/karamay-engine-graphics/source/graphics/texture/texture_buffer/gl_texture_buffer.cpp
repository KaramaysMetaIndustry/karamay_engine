#include "gl_texture_buffer.h"

gl_texture_buffer::gl_texture_buffer()
{
	glCreateTextures(GL_TEXTURE_BUFFER, 1, &_handle);
}

gl_texture_buffer::~gl_texture_buffer()
{
	glDeleteTextures(1, &_handle);
}

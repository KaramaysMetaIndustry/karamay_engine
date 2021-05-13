#include "gl_texture_2d_array_multisample.h"

gl_multisample_texture_2d_array::gl_multisample_texture_2d_array()
{
	glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 1, &_handle);
}

gl_multisample_texture_2d_array::~gl_multisample_texture_2d_array()
{
	glDeleteTextures(1, &_handle);
}

void gl_multisample_texture_2d_array::bind(GLuint Unit)
{
	glActiveTexture(Unit);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, _handle);
}

void gl_multisample_texture_2d_array::unbind()
{
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, _handle);
	glActiveTexture(0);
}


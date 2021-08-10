#include "gl_texture_2d_array_multisample.h"

void gl_texture_2d_array_multisample::bind(GLuint Unit)
{
	glActiveTexture(Unit);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, _handle);
}

void gl_texture_2d_array_multisample::unbind()
{
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, _handle);
	glActiveTexture(0);
}


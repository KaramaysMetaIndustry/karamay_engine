#include "gl_texture_1d_array.h"

void gl_texture_1d_array::bind(std::uint32_t unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_1D_ARRAY, _handle);
}

void gl_texture_1d_array::unbind()
{
	GLint CurrentHandle = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_1D_ARRAY, &CurrentHandle);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_1D_ARRAY, 0);
	glActiveTexture(GL_TEXTURE0);
}



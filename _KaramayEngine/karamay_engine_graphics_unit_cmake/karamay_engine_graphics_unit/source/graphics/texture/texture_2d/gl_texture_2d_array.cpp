#include "gl_texture_2d_array.h"

void gl_texture_2d_array::unbind()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	glActiveTexture(GL_TEXTURE0);
}



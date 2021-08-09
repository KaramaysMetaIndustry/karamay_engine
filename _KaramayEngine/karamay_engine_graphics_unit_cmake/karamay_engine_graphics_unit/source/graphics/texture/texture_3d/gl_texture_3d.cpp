#include "gl_texture_3d.h"


void gl_texture_3d::bind(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_3D, _handle);
}

void gl_texture_3d::unbind()
{
	glBindTexture(GL_TEXTURE_3D, 0);
	glActiveTexture(GL_TEXTURE0);
}

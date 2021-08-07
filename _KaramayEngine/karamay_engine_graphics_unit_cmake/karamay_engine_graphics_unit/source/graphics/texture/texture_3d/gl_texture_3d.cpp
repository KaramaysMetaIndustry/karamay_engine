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

gl_texture_3d::gl_texture_3d()
{
	glCreateTextures(GL_TEXTURE_3D, 1, &_handle);
}

gl_texture_3d::~gl_texture_3d()
{
}

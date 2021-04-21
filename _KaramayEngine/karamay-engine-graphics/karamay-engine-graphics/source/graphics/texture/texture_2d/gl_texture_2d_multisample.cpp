#include "gl_texture_2d_multisample.h"

gl_multisample_texture_2d::gl_multisample_texture_2d()
{
	glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &_handle);
}

gl_multisample_texture_2d::~gl_multisample_texture_2d()
{
	glDeleteTextures(1, &_handle);
}

void gl_multisample_texture_2d::bind(unsigned int unit)
{
	glActiveTexture(unit);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _handle);
}

void gl_multisample_texture_2d::unbind()
{
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _handle);
	glActiveTexture(0);
}

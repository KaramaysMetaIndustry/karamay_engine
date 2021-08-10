#include "gl_texture_2d_multisample.h"

void gl_texture_2d_multisample::bind(std::uint32_t unit)
{
	glActiveTexture(unit);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _handle);
}

void gl_texture_2d_multisample::unbind()
{
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, _handle);
	glActiveTexture(0);
}

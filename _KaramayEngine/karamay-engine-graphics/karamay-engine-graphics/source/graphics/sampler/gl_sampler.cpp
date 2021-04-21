#include "gl_sampler.h"

void gl_sampler::bind(unsigned int unit)
{
	if (!(unit >= 0 && unit < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)) return;

	glBindSampler(unit, _handle);
}

void gl_sampler::unbind()
{

}

gl_sampler::gl_sampler()
{
	glCreateSamplers(1, &_handle);
}

gl_sampler::~gl_sampler()
{
	glDeleteSamplers(1, &_handle);
}

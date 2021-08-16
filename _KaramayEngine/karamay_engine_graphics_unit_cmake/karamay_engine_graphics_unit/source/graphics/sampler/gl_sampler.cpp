#include "gl_sampler.h"

gl_sampler::~gl_sampler()
{
	glDeleteSamplers(1, &_handle);
}



#include "gl_texture_1d.h"
#include "graphics/sampler/gl_sampler.h"

gl_texture_1d::gl_texture_1d()
{
	glCreateTextures(GL_TEXTURE_1D, 1, &_handle);
}

gl_texture_1d::~gl_texture_1d()
{
	glDeleteTextures(1, &_handle);
}

void* gl_texture_1d::fetch_pixels(GLuint mipmap_index, GLenum format, GLenum type)
{
	void* pixels = nullptr;
	glGetTexImage(GL_TEXTURE_1D, mipmap_index, format, type, pixels);
	return pixels;
}

void gl_texture_1d::bind(std::uint32_t unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_1D, _handle);
	if (_sampler)
	{
		_sampler->bind(unit);
	}
}

void gl_texture_1d::unbind()
{
}


#include "gl_texture_1d.h"
#include "graphics/sampler/gl_sampler.h"

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


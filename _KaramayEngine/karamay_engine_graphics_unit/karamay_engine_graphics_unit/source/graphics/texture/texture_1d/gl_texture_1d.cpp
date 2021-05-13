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

void gl_texture_1d::allocate(gl_texture_enum::internal_format internal_format, std::uint32_t base_mipmap_width, std::uint32_t mipmaps_num)
{
	glTextureStorage1D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), base_mipmap_width);
	_internal_format = internal_format;
	_base_mipmap_width = base_mipmap_width;
	_mipmaps_num = mipmaps_num;
}

void gl_texture_1d::clear_mipmap(int mipmap_index, int x_offset, int width, GLenum format, GLenum type, const void* data)
{
	glClearTexSubImage(_handle, mipmap_index, x_offset, 0, 0, width, 0, 0, format, type, data);
}

void gl_texture_1d::invalidate_mipmap(int mipmap_index)
{
	invalidate_sub_mipmap(mipmap_index, 0, _base_mipmap_width);
}

void gl_texture_1d::invalidate_sub_mipmap(int mipmap_index, int x_offset, int width)
{
	glInvalidateTexSubImage(_handle, mipmap_index, x_offset, 0, 0, width, 0, 0);
}

void* gl_texture_1d::fetch_pixels(GLuint mipmap_index, GLenum format, GLenum type)
{
	void* pixels = nullptr;
	glGetTexImage(GL_TEXTURE_1D, mipmap_index, format, type, pixels);
	return pixels;
}

void gl_texture_1d::bind(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_1D, _handle);
	_sampler->bind(unit);
}

void gl_texture_1d::unbind()
{
	glBindTexture(GL_TEXTURE_1D, 0);
	glActiveTexture(0);
	_sampler->unbind();
}

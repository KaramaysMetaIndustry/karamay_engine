#include "gl_texture_1d.h"

gl_texture_1d::gl_texture_1d()
{
	glCreateTextures(GL_TEXTURE_1D, 1, &_handle);
}

gl_texture_1d::~gl_texture_1d()
{
	glDeleteTextures(1, &_handle);
}

void gl_texture_1d::allocate(GLenum internal_format, int base_mipmap_width, int mipmaps_num)
{
	glTextureStorage1D(_handle, mipmaps_num, internal_format, base_mipmap_width);
	_internal_format = internal_format;
	_base_mipmap_width = base_mipmap_width;
	_mipmaps_num = mipmaps_num;
}

void gl_texture_1d::fill_base_mipmap(GLenum format, gl_texture_data_type type, const void* pixels)
{
	glTexSubImage1D(GL_TEXTURE_1D, 0, 0, _base_mipmap_width, format, static_cast<GLenum>(type), pixels);
}

void gl_texture_1d::fill_base_sub_mipmap(GLenum format, gl_texture_data_type type, const void* pixels, int x_offset, int sub_mipmap_width)
{
	glTexSubImage1D(GL_TEXTURE_1D, 0, x_offset, sub_mipmap_width, format, static_cast<GLenum>(type), pixels);
}

void gl_texture_1d::fill_miniature_mipmap(GLenum format, gl_texture_data_type type, const void* data, int mipmap_index)
{
	glTexSubImage1D(GL_TEXTURE_1D, mipmap_index, 0, 0, format, static_cast<GLenum>(type), data);
}

void gl_texture_1d::fill_miniature_mipmaps()
{
	glGenerateMipmap(GL_TEXTURE_1D);
}

void gl_texture_1d::clear()
{
	//glClearTexImage()
}

void gl_texture_1d::invalidate_mipmap(int mipmap_index)
{
	invalidate_sub_mipmap(mipmap_index, 0, _base_mipmap_width);
}

void gl_texture_1d::invalidate_sub_mipmap(int mipmap_index, int x_offset, int width)
{
	glInvalidateTexSubImage(_handle, mipmap_index, x_offset, 0, 0, width, 0, 0);
}

void gl_texture_1d::bind(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_1D, _handle);
}

void gl_texture_1d::unbind()
{
	glBindTexture(GL_TEXTURE_1D, 0);
	glActiveTexture(0);
}

#include "gl_texture_1d_array.h"

gl_texture_1d_array::gl_texture_1d_array()
{
}

gl_texture_1d_array::~gl_texture_1d_array()
{
}

void gl_texture_1d_array::allocate(GLenum internal_format, int width, int mipmaps_num, int num)
{
	glTextureStorage2D(_handle, mipmaps_num, internal_format, width, num);
	_num = num;
	_mipmaps_num = mipmaps_num;
	_internal_format = internal_format;
	_width = width;
}

void gl_texture_1d_array::fill_element_base_mipmap(GLenum format, GLenum type, const void* data, int element_index)
{
	fill_element_miniature_mipmap(format, type, data, element_index, 0);
}

void gl_texture_1d_array::fill_element_base_sub_mipmap(GLenum format, GLenum type, const void* data, int x_offset, int width, int element_index)
{
}

void gl_texture_1d_array::fill_element_miniature_mipmap(GLenum format, GLenum type, const void* data, int element_index, int mipmap_index)
{
	glTexImage2D(GL_TEXTURE_1D_ARRAY, mipmap_index, _internal_format, _width, element_index, 0, format, type, data);
}

void gl_texture_1d_array::fill_element_miniature_sub_mipmap(GLenum format, GLenum type, const void* data, int x_offset, int width, int element_index, int mipmap_index)
{
}

void gl_texture_1d_array::fill_array_miniature_mipmaps()
{
	glGenerateMipmap(GL_TEXTURE_1D_ARRAY);
}

void gl_texture_1d_array::bind(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_1D_ARRAY, _handle);
}

void gl_texture_1d_array::unbind()
{
	GLint CurrentHandle = 0;
	glGetIntegerv(GL_TEXTURE_BINDING_1D_ARRAY, &CurrentHandle);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_1D_ARRAY, 0);
	glActiveTexture(GL_TEXTURE0);
}



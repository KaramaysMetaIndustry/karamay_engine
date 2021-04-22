#include "gl_texture_2d_array.h"

gl_texture_2d_array::gl_texture_2d_array()
{
	glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &_handle);
}

gl_texture_2d_array::~gl_texture_2d_array()
{
	glDeleteTextures(1, &_handle);
}

void gl_texture_2d_array::allocate(GLenum internal_format, GLsizei width, GLsizei height, int mipmaps_num, GLsizei num)
{
	glTextureStorage3D(_handle, mipmaps_num, internal_format, width, height, num);
	_width = width;
	_height = height;
	_num = num;
	_internal_format = internal_format;
	_mipmaps_num = mipmaps_num;
}

void gl_texture_2d_array::fill_element_base_mipmap(GLenum format, GLenum type, const void* data, int element_index)
{
	fill_element_miniature_mipmap(format, type, data, 0, element_index);
}

void gl_texture_2d_array::fill_element_base_sub_mipmap(GLenum format, GLenum type, const void* data, int x_offset, int y_offset, int width, int height, int element_index)
{
	fill_element_miniature_sub_mipmap(format, type, data, x_offset, y_offset, width, height, 0, element_index);
}

void gl_texture_2d_array::fill_element_miniature_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index, int element_index)
{
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, mipmap_index, 0, 0, element_index, _width, _height, 0, format, type, data);
}

void gl_texture_2d_array::fill_element_miniature_sub_mipmap(GLenum format, GLenum type, const void* data, int x_offset, int y_offset, int width, int height, int mipmap_index, int element_index)
{
	glTexSubImage3D(GL_TEXTURE_2D_ARRAY, mipmap_index, x_offset, y_offset, element_index, width, height, 0, format, type, data);
}

void gl_texture_2d_array::fill_array_miniature_mipmaps()
{
	glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
}

void gl_texture_2d_array::bind(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D_ARRAY, _handle);
}

void gl_texture_2d_array::unbind()
{
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	glActiveTexture(GL_TEXTURE0);
}



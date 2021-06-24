#include "gl_texture_3d.h"

void gl_texture_3d::allocate(GLenum internal_format, int width, int height, int depth, int mipmaps_num)
{
	glTextureStorage3D(_handle, mipmaps_num, internal_format, width, height, depth);
}

void gl_texture_3d::fill_base_mipmap(GLenum format, GLenum type, const void* data)
{
	fill_miniature_sub_mipmap(format, type, data, 0, 0, 0, 0, _width, _height, _depth);
}

void gl_texture_3d::fill_miniature_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index)
{
	fill_miniature_sub_mipmap(format, type, data, mipmap_index, 0, 0, 0, _width, _height, _depth);
}

void gl_texture_3d::fill_base_sub_mipmap(GLenum format, GLenum type, const void* data, int x_offset, int y_offset, int z_offset, int width, int height, int depth)
{
	fill_miniature_sub_mipmap(format, type, data, 0, x_offset, y_offset, z_offset, width, height, depth);
}

void gl_texture_3d::fill_miniature_sub_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index, int x_offset, int y_offset, int z_offset, int width, int height, int depth)
{
	glTexSubImage3D(GL_TEXTURE_3D, mipmap_index, x_offset, y_offset, z_offset, width, height, depth, format, type, data);
}

void gl_texture_3d::bind(unsigned int unit)
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_3D, _handle);
}

void gl_texture_3d::unbind()
{
	glBindTexture(GL_TEXTURE_3D, 0);
	glActiveTexture(GL_TEXTURE0);
}

gl_texture_3d::gl_texture_3d()
{
	glCreateTextures(GL_TEXTURE_3D, 1, &_handle);
}

gl_texture_3d::~gl_texture_3d()
{
}

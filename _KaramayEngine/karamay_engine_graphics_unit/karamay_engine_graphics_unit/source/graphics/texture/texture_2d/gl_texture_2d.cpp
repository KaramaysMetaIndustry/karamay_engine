#include "gl_texture_2d.h"

gl_texture_2d::gl_texture_2d()
{
}

gl_texture_2d::~gl_texture_2d()
{
}

void gl_texture_2d::fill_base_mipmap(GLenum format, GLenum type, const void* data)
{
	fill_miniature_mipmap(format, type, data, 0);
}

void gl_texture_2d::fill_miniature_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index)
{
	glTexSubImage2D(GL_TEXTURE_2D, mipmap_index, 0, 0, _width, _height, format, type, data);
}

void gl_texture_2d::fill_base_sub_mipmap(GLenum format, GLenum type, const void* data, int x_offset, int y_offset, int width, int height)
{
	fill_miniature_sub_mipmap(format, type, data, 0, x_offset, y_offset, width, height);
}

void gl_texture_2d::fill_miniature_sub_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index, int x_offset, int y_offset, int width, int height)
{
	glTexSubImage2D(GL_TEXTURE_2D, mipmap_index, x_offset, y_offset, width, height, format, type, data);
}

void gl_texture_2d::fill_miniature_mipmaps()
{
	glGenerateMipmap(GL_TEXTURE_2D);
}

void gl_texture_2d::bind()
{
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, _handle);
}

void gl_texture_2d::unbind()
{
	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
}

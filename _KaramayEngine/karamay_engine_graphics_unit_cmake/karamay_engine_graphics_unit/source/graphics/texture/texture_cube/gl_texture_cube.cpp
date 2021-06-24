#include "gl_texture_cube.h"

void gl_texture_cube::allocate(GLenum internal_format, int width, int mipmaps_num)
{
	glTextureStorage3D(GL_TEXTURE_CUBE_MAP, mipmaps_num, internal_format, width, _width, 6);
}

void gl_texture_cube::fill_base_mipmap(GLenum format, GLenum type, const void* data, e_cube_face face_index)
{
	fill_miniature_sub_mipmap(format, type, data, face_index, 0, 0, 0, _width, _width);
}

void gl_texture_cube::fill_base_sub_mipmap(GLenum format, GLenum type, const void* data, e_cube_face face_index, int x_offset, int y_offset, int width, int height)
{
	fill_miniature_sub_mipmap(format, type, data, face_index, 0, x_offset, y_offset, width, height);
}

void gl_texture_cube::fill_miniature_mipmap(GLenum format, GLenum type, const void* data, e_cube_face face_index, int mipmap_index)
{
	fill_miniature_sub_mipmap(format, type, data, face_index, mipmap_index, 0, 0, _width, _width);
}

void gl_texture_cube::fill_miniature_sub_mipmap(GLenum format, GLenum type, const void* data, e_cube_face face_index, int mipmap_index, int x_offset, int y_offset, int width, int height)
{
	glTexSubImage2D(static_cast<GLenum>(face_index), mipmap_index, x_offset, y_offset, width, height, format, type, data);
}

void gl_texture_cube::fill_cube_miniature_mipmaps()
{
	glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}

gl_texture_cube::gl_texture_cube()
{
}

gl_texture_cube::~gl_texture_cube()
{
}

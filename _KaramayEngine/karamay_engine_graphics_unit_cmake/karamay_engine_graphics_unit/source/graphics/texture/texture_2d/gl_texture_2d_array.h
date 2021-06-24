#pragma once
#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_2d_array final : public gl_texture_base
{
public:
	void allocate(GLenum internal_format, GLsizei width, GLsizei height, int mipmaps_num, GLsizei num);

	void fill_element_base_mipmap(GLenum format, GLenum type, const void* data, int element_index);
	void fill_element_miniature_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index, int element_index);

	void fill_element_base_sub_mipmap(GLenum format, GLenum type, const void* data, int x_offset, int y_offset, int width, int height, int element_index);
	void fill_element_miniature_sub_mipmap(GLenum format, GLenum type, const void* data, int x_offset, int y_offset, int width, int height, int mipmap_index, int element_index);

	void fill_array_miniature_mipmaps();

	void bind(unsigned int unit);
	void unbind();
	

private:
	int _width, _height, _num;

	int _internal_format;

	int _mipmaps_num;

public:
	gl_texture_2d_array();
	~gl_texture_2d_array();
};


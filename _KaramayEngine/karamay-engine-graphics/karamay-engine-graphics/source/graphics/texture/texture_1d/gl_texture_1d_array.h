#pragma once
#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_1d_array final : public gl_texture_base
{
public:
	void allocate(GLenum internal_format, int width, int mipmaps_num, int num);

	void fill_element_base_mipmap(GLenum format, GLenum type, const void* data, int element_index);
	void fill_element_base_sub_mipmap(GLenum format, GLenum type, const void* data, int x_offset, int width, int element_index);
	void fill_element_miniature_mipmap(GLenum format, GLenum type, const void* data, int element_index, int mipmap_index);
	void fill_element_miniature_sub_mipmap(GLenum format, GLenum type, const void* data, int x_offset, int width, int element_index, int mipmap_index);

	void fill_array_miniature_mipmaps();

	void bind(unsigned int unit);
	void unbind();

private:
	int _num;

	int _mipmaps_num;

	GLenum _internal_format;

	int _width;

public:
	gl_texture_1d_array();
	virtual ~gl_texture_1d_array();

};


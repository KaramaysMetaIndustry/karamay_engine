#pragma once
#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_2d final : public gl_texture_base
{
public:
	void allocate(GLenum internal_format, GLsizei width, GLsizei height, int mipmaps_num);

	void fill_base_mipmap(GLenum format, GLenum type, const void* data);
	void fill_miniature_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index);

	void fill_base_sub_mipmap(GLenum format, GLenum type, const void* data, int x_offset, int y_offset, int width, int height);
	void fill_miniature_sub_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index, int x_offset, int y_offset, int width, int height);
	
	void fill_miniature_mipmaps();

	void bind();
	void unbind();

	std::uint32_t get_unit() { return 0; }

private:
	int _width, _height;

	int _internal_format;

	int _mipmaps_num;

public:
	gl_texture_2d();
	~gl_texture_2d();
};

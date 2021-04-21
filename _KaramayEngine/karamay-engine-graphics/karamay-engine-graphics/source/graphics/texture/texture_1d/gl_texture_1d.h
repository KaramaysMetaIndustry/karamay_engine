#pragma once
#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_1d final : public gl_texture_base
{
public:
	void allocate(GLenum internal_format, int base_mipmap_width, int mipmaps_num);

	void fill_base_mipmap(GLenum format, GLenum type, const void* pixels);
	void fill_base_sub_mipmap(GLenum format, GLenum type, const void* pixels, int x_offset, int base_sub_mipmap_width);

	void fill_miniature_mipmaps();

	void fill_miniature_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index);
	void fill_miniature_sub_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index, int x_offset, int width) {}

	void clear();

	void download_mipmap(GLenum format, GLenum type, void* data, int mipmap_index) {
		glGetTexImage(GL_TEXTURE_1D, mipmap_index, format, type, data);
	}

	/// invalidate image
	void invalidate_mipmap(int mipmap_index);
	void invalidate_sub_mipmap(int mipmap_index, int x_offset, int width);

	void copy() {
		//glCopyImageSubData(handle)
	}

	/// bind & unbind
	void bind(unsigned int unit);

	void unbind();

private:
	unsigned int _internal_format;

	int _mipmaps_num;

	int _base_mipmap_width;


public:
	gl_texture_1d();

	~gl_texture_1d();
};


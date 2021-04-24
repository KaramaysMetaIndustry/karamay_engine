#pragma once
#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_1d final : public gl_texture_base
{
private:
	/**
	 * construct texture_1d
	 * create texture 1d object at client, keep the handle of it
	 * but now it do not have real memory at GPU
	 */
	gl_texture_1d();

public:
	static std::shared_ptr<gl_texture_1d> construct();

	~gl_texture_1d();

public:
	/**
	 * allocate memory at GPU, create mapping between client and GPU
	 */
	void allocate(GLenum internal_format, int base_mipmap_width, int mipmaps_num);

	/**
	 * fill the base mipmap (GPU memory)
	 */
	void fill_base_mipmap(GLenum format, gl_texture_data_type type, const void* pixels);
	void fill_base_sub_mipmap(GLenum format, gl_texture_data_type type, const void* pixels, int x_offset, int base_sub_mipmap_width);

	/**
	 * fill the rest all mipmap auto
	 */
	void fill_miniature_mipmaps();

	/**
	 * fill the rest mipmap manually
	 */
	void fill_miniature_mipmap(GLenum format, gl_texture_data_type type, const void* data, int mipmap_index);
	void fill_miniature_sub_mipmap(GLenum format, gl_texture_data_type type, const void* data, int mipmap_index, int x_offset, int width)
	{}


	/**
	 * fills image with a constant value
	 */
	void clear_mipmap(int mipmap_index, int x_offset, int width, GLenum format, GLenum type, const void* data);

	
	void invalidate_mipmap(int mipmap_index);
	void invalidate_sub_mipmap(int mipmap_index, int x_offset, int width);

	/**
	 * read pixels from GPU to client memory
	 */
	void* fetch_pixels(GLuint mipmap_index, GLenum format, GLenum type);
	void* fetch_base_mipmap_pixels(GLenum format, GLenum type) {}

public:
	void bind(unsigned int unit);

	void unbind();

private:
	unsigned int _internal_format; // internal_format 指定了存储结构，format && type 指定了传入输入的存储结构，当后者与前者不符合时，尝试将后者转化为前者

	int _mipmaps_num;

	int _base_mipmap_width;

public:
	unsigned int get_internal_format() const {return _internal_format;};

};


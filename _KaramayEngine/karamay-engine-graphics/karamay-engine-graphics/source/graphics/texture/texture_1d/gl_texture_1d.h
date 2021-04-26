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


private:
	/**
	 * specify the texture's storage format int the GPU memory
	 */
	gl_texture_internal_format _internal_format;

	/**
	 * specify the max num of mipmaps this texture can have
	 */
	unsigned int _mipmaps_num;

	/**
	 * specify the base mipmap's width
	 */
	unsigned int _base_mipmap_width;

public:
	static std::shared_ptr<gl_texture_1d> construct();

	~gl_texture_1d();

public:
	/**
	 * allocate memory at GPU, create mapping between client and GPU
	 */
	void allocate(gl_texture_internal_format internal_format, unsigned int base_mipmap_width, unsigned int mipmaps_num);

public:

	void fill_base_mipmap(gl_texture_pixels_package pixels_package)
	{
		glTexSubImage1D(GL_TEXTURE_1D, 0, 0, _base_mipmap_width, static_cast<GLenum>(pixels_package.format), static_cast<GLenum>(pixels_package.type), pixels_package.pixels);
	}


	void fill_base_sub_mipmap(gl_texture_pixels_package pixels_package, int x_offset) {}


	void fill_miniature_mipmaps_automatically() {
		bind(1);
		glGenerateMipmap(GL_TEXTURE_1D);
		unbind();
	}

public:

	void fill_mipmap(const gl_texture_pixels_package& pixels_package, unsigned int mipmap_index)
	{
		fill_sub_mipmap(pixels_package, mipmap_index, 0);
	}

	void fill_sub_mipmap(const gl_texture_pixels_package& pixels_package, unsigned int mipmap_index, int x_offset) 
	{
		glTexSubImage1D(GL_TEXTURE_1D, mipmap_index, x_offset, pixels_package.width, static_cast<GLenum>(pixels_package.format), static_cast<GLenum>(pixels_package.type), pixels_package.pixels);
	}


public:

	void fill_base_mipmap(GLenum format, gl_texture_data_type type, const void* pixels);
	void fill_base_sub_mipmap(GLenum format, gl_texture_data_type type, const void* pixels, int x_offset, int base_sub_mipmap_width);

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

public:
	gl_texture_internal_format get_internal_format() const {return _internal_format;};

};


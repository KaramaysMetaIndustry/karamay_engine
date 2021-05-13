#pragma once
#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_1d final : public gl_texture_base
{
public:

	gl_texture_1d();

	virtual ~gl_texture_1d();
	
public:
	
	void bind(std::uint32_t unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_1D, _handle);
		if (_sampler)
		{
			_sampler->bind(unit);
		}
	}

	void unbind()
	{
	}

public:
	
	void allocate(gl_texture_enum::internal_format internal_format, std::uint32_t base_mipmap_width, std::uint32_t mipmaps_num);

	void fill_mipmap(std::uint32_t mipmap_index, std::uint32_t x_offset, std::uint32_t mipmap_width, gl_texture_pixels_pack pixels_pack)
	{
		glTexSubImage1D(GL_TEXTURE_1D, mipmap_index, x_offset, mipmap_width, 
			static_cast<GLenum>(pixels_pack.format), static_cast<GLenum>(pixels_pack.type), 
			pixels_pack.pixels);
	}

public:

	/**
	 * fill the rest mipmap manually
	 */
	void fill_miniature_mipmap(GLenum format, gl_texture_enum::pixels_type type, const void* data, int mipmap_index)
	{
		glTexSubImage1D(GL_TEXTURE_1D, mipmap_index, 0, 0, format, static_cast<GLenum>(type), data);
	}

	void fill_miniature_sub_mipmap(GLenum format, gl_texture_enum::pixels_type type, const void* data, int mipmap_index, int x_offset, int width)
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
	
private:

	gl_texture_enum::internal_format _internal_format;

	std::uint32_t _mipmaps_num;

	std::uint32_t _base_mipmap_width;

};


#pragma once
#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_1d final : public gl_texture_base
{
public:

	gl_texture_1d();

	virtual ~gl_texture_1d();
	
private:

	gl_texture_enum::internal_format _internal_format;

	std::uint32_t _mipmaps_num;

	std::uint32_t _base_mipmap_width;

public:
	
	void allocate(gl_texture_enum::internal_format internal_format, std::uint32_t base_mipmap_width, std::uint32_t mipmaps_num)
	{
		glTextureStorage1D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), base_mipmap_width);
		_internal_format = internal_format;
		_base_mipmap_width = base_mipmap_width;
		_mipmaps_num = mipmaps_num;
	}

	void fill(std::int32_t x_offset, std::int32_t mipmap_width, const void* pixels, gl_texture_enum::pixels_format pixels_format, gl_texture_enum::pixels_type pixels_type, std::int32_t mipmap_index = 0)
	{
		if (pixels)
		{
			glTexSubImage1D(GL_TEXTURE_1D, mipmap_index, x_offset, mipmap_width, static_cast<GLenum>(pixels_format), static_cast<GLenum>(pixels_type), pixels);
		}
	}

	void clear(std::int32_t x_offset, std::int32_t width, const void* data, GLenum format, GLenum type, int mipmap_index = 0)
	{
		if (data)
		{
			glClearTexSubImage(_handle, mipmap_index, x_offset, 0, 0, width, 0, 0, format, type, data);
		}
	}

	void invalidate_mipmap(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t width)
	{
		glInvalidateTexSubImage(_handle, mipmap_index, x_offset, 0, 0, width, 0, 0);
	}

	void* fetch_pixels(GLuint mipmap_index, GLenum format, GLenum type);
	
public:

	void bind(std::uint32_t unit);

	void unbind();

};


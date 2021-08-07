#ifndef H_GL_TEXTURE_2D
#define H_GL_TEXTURE_2D

#include "graphics/texture/base/gl_texture.h"

template<gl_texture_pixel_format format>
class gl_pixels
{
public:

	gl_pixels(std::int32_t count, const void* data) {}

public:

	gl_texture_pixel_format get_format() const { return format; }

	void* get_data();

private:

	std::vector<int> pixels;

};

class gl_texture_2d_base : public gl_texture
{
public:

	void bind(std::uint32_t unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D, _handle);
	}

	void unbind();
};

template<gl_texture_pixel_format format>
class gl_texture_2d final : public gl_texture_2d_base
{
public:
	
	explicit gl_texture_2d(std::int32_t mipmaps_count, std::int32_t width, std::int32_t height) :
		_mipmaps_count(mipmaps_count),
		_width(width),
		_height(height)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &_handle);
		glTextureStorage2D(_handle, _mipmaps_count, static_cast<GLenum>(format), _width, _height);
		//glActiveTexture(GL_TEXTURE0);
		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
	}
	
	virtual ~gl_texture_2d() = default;

private:
	
	gl_texture_2d() = default;

	std::int32_t _mipmaps_count, _width, _height

public:

	gl_texture_pixel_format get_format() const { return format; }

	std::pair<std::int32_t, std::int32_t> inline get_mipmap_size(std::uint32_t mipmap_index) const
	{
		return std::make_pair(_width >> mipmap_index, _height >> mipmap_index);
	}

public:

	/*
	* index of mipmap
	* x offset(unit = pixel), y offset(uint = pixel)
	* in_pixels
	*/
	void fill(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset)
	{
		if (mipmap_index < 0 || mipmap_index >= _mipmaps_count || x_offset < 0 || y_offset < 0 || x_offset >= _width || y_offset >= _height) return;

		glBindTexture(GL_TEXTURE_2D, _handle);
		auto data_format = pixel_format_to_data_format(_descriptor.pixel_format);
		glTexSubImage2D(GL_TEXTURE_2D, mipmap_index,
			x_offset, y_offset, _descriptor.width, _descriptor.height,
			static_cast<std::uint32_t>(data_format.first), static_cast<std::uint32_t>(data_format.second), pixels.get_data());
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void fetch_pixels(std::int32_t mipmap_index, gl_pixels<format>& out_pixels)
	{
		glGetTexImage(GL_TEXTURE_2D)
	}

};

#endif

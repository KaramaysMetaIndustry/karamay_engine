#ifndef H_GL_TEXTURE_2D
#define H_GL_TEXTURE_2D

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_2d_descriptor
{
	/* pixels num = width * height */
	std::int32_t width, height;
	/* combination of a pixel */
	gl_texture_pixel_format pixel_format;
	/* num of mipmaps (include base image) */
	std::int32_t mipmaps_count;

	/* whole params for constructing texture 2d */
	explicit gl_texture_2d_descriptor(std::int32_t _width, std::int32_t _height, gl_texture_pixel_format _pixel_format, std::int32_t _mipmaps_count) :
		width(_width), height(_height),
		pixel_format(_pixel_format),
		mipmaps_count(_mipmaps_count)
	{}

	/* 
	* _width : 
	* _height : 
	* _pixel_format: 
	*/
	explicit gl_texture_2d_descriptor(std::int32_t _width, std::int32_t _height, gl_texture_pixel_format _pixel_format) :
		width(_width), height(_height),
		pixel_format(_pixel_format),
		mipmaps_count(1)
	{}

	gl_texture_2d_descriptor() = delete;
	gl_texture_2d_descriptor(const gl_texture_2d_descriptor&) = default;
	gl_texture_2d_descriptor& operator=(const gl_texture_2d_descriptor&) = default;
	
	~gl_texture_2d_descriptor() = default;
};


class gl_texture_2d final : public gl_texture
{
public:
	
	explicit gl_texture_2d(const gl_texture_2d_descriptor& descriptor) :
		_descriptor(descriptor)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &_handle);
		glTextureStorage2D(
			_handle, _descriptor.mipmaps_count, 
			static_cast<GLenum>(_descriptor.pixel_format), 
			_descriptor.width, _descriptor.height
		);
	}

	gl_texture_2d() = delete;
	
	virtual ~gl_texture_2d() = default;

public:

	void bind() override
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, _handle);
	}

	void unbind() override
	{

	}

private:

	gl_texture_2d_descriptor _descriptor;

public:

	gl_texture_2d_descriptor get_descriptor() const { return _descriptor; }


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

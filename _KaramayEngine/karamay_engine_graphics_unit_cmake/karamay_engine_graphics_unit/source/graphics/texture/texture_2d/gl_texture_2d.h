#ifndef H_GL_TEXTURE_2D
#define H_GL_TEXTURE_2D

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_2d_descriptor : public gl_texture_descriptor
{
	/* pixels num = width * height */
	std::int32_t width, height;
	/* combination of a pixel */
	gl_texture_pixel_format pixel_format;
	/* num of mipmaps (include base image) */
	std::int32_t mipmaps_count;

	explicit gl_texture_2d_descriptor(
		std::int32_t _width, std::int32_t _height, 
		gl_texture_pixel_format _pixel_format, 
		std::int32_t _mipmaps_count
	) :
		width(_width), height(_height),
		pixel_format(_pixel_format),
		mipmaps_count(_mipmaps_count),
		gl_texture_descriptor()
	{}

	explicit gl_texture_2d_descriptor(
		std::int32_t _width, std::int32_t _height, 
		gl_texture_pixel_format _pixel_format
	) :
		width(_width), height(_height),
		pixel_format(_pixel_format),
		mipmaps_count(1),
		gl_texture_descriptor()
	{}

	gl_texture_2d_descriptor() = delete;
	gl_texture_2d_descriptor(const gl_texture_2d_descriptor&) = default;
	gl_texture_2d_descriptor& operator=(const gl_texture_2d_descriptor&) = default;
	
	~gl_texture_2d_descriptor() = default;
};

class gl_texture_2d final : public gl_texture
{
public:
	gl_texture_2d() = delete;
	explicit gl_texture_2d(const gl_texture_2d_descriptor& descriptor) :
		gl_texture(gl_texture_type::TEXTURE_2D),
		_descriptor(descriptor)
	{
		glTextureStorage2D(_handle, 
			_descriptor.mipmaps_count, 
			static_cast<std::uint32_t>(_descriptor.pixel_format), 
			_descriptor.width, _descriptor.height
		);
	}

	
	~gl_texture_2d() = default;

public:

	void bind() override
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, _handle);
	}

	void unbind() override {}

private:

	gl_texture_2d_descriptor _descriptor;

public:

	const gl_texture_2d_descriptor& descriptor() const { return _descriptor; }

	void fill(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset)
	{
		if (
			mipmap_index < 0 || 
			mipmap_index >= _descriptor.mipmaps_count || 
			x_offset < 0 || y_offset < 0 || 
			x_offset >= _descriptor.width || 
			y_offset >= _descriptor.height
			) return;

		auto data_format = pixel_format_to_data_format(_descriptor.pixel_format);
		glTextureSubImage2D(_handle, 
			mipmap_index,
			x_offset, y_offset, _descriptor.width, _descriptor.height,
			static_cast<std::uint32_t>(data_format.first), 
			static_cast<std::uint32_t>(data_format.second), 
			pixels.get_data()
		);

	}

	void fetch_pixels(std::int32_t mipmap_index)
	{
		glGetTextureImage(_handle, 0, );
	}

};

#endif

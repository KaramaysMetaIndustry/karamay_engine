#ifndef H_GL_TEXTURE_2D_ARRAY
#define H_GL_TEXTURE_2D_ARRAY

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_2d_array_descriptor
{
	std::int32_t elements_count;
	std::int32_t width, height;
	gl_texture_pixel_format pixel_format;
	std::int32_t mipmaps_count;

	gl_texture_2d_array_descriptor(std::int32_t _elements_count, std::int32_t _width, std::int32_t _height, gl_texture_pixel_format _pixel_format, std::int32_t _mipmaps_count) :
		elements_count(_elements_count),
		width(_width), height(_height),
		pixel_format(_pixel_format),
		mipmaps_count(_mipmaps_count)
	{}

	gl_texture_2d_array_descriptor(std::int32_t _elements_count, std::int32_t _width, std::int32_t _height, gl_texture_pixel_format _pixel_format) :
		elements_count(_elements_count),
		width(_width), height(_height),
		pixel_format(_pixel_format),
		mipmaps_count(1)
	{}

	gl_texture_2d_array_descriptor() = delete;

	gl_texture_2d_array_descriptor(const gl_texture_2d_array_descriptor&) = default;

	~gl_texture_2d_array_descriptor() = default;

};

class gl_texture_2d_array final : public gl_texture
{
public:

	explicit gl_texture_2d_array(const gl_texture_2d_array_descriptor& descriptor) : 
		gl_texture(gl_texture_type::TEXTURE_2D_ARRAY),
		_descriptor(descriptor)
	{
		glTextureStorage3D(_handle,
			_descriptor.mipmaps_count, static_cast<GLenum>(_descriptor.pixel_format),
			_descriptor.width, _descriptor.height,
			_descriptor.elements_count
		);
	}

	gl_texture_2d_array() = delete;
	gl_texture_2d_array(const gl_texture_2d_array&) = delete;
	gl_texture_2d_array& operator=(const gl_texture_2d_array&) = delete;

	~gl_texture_2d_array() override = default;

private:
	
	gl_texture_2d_array_descriptor _descriptor;

public:

	gl_texture_2d_array_descriptor get_descriptor() const { return _descriptor; }

	void fill(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, const void*data)
	{
		std::int32_t _width = 0;
		std::int32_t _height = 0;
		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY, 
			mipmap_index, x_offset, y_offset, 
			element_index, _width, _height, 1,
			static_cast<GLenum>(_descriptor.pixel_format), type, 
			data
		);
	}

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_2D_ARRAY, _handle);
		glGenerateMipmap(GL_TEXTURE_2D_ARRAY);
		glBindTexture(GL_TEXTURE_2D_ARRAY, 0);
	}

	void bind(std::uint32_t unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_2D_ARRAY, _handle);
	}

	void unbind();

};

#endif
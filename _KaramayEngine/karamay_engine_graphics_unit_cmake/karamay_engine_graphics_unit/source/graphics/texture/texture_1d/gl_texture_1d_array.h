#ifndef H_GL_TEXTURE_1D_ARRAY
#define H_GL_TEXTURE_1D_ARRAY

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_1d_array_descriptor
{
	std::int32_t elements_count;
	std::int32_t length;
	gl_texture_pixel_format pixel_format;
	std::int32_t mipmaps_count;

	gl_texture_1d_array_descriptor(std::int32_t _elements_count, std::int32_t _length, gl_texture_pixel_format _pixel_format, std::int32_t _mipmaps_count) :
		elements_count(_elements_count),
		length(_length),
		pixel_format(_pixel_format),
		mipmaps_count(_mipmaps_count)
	{}

	gl_texture_1d_array_descriptor(std::int32_t _elements_count, std::int32_t _length, gl_texture_pixel_format _pixel_format) :
		elements_count(_elements_count),
		length(_length),
		pixel_format(_pixel_format),
		mipmaps_count(1)
	{}

	gl_texture_1d_array_descriptor() = delete;

	gl_texture_1d_array_descriptor(const gl_texture_1d_array_descriptor&) = default;

};

class gl_texture_1d_array final : public gl_texture
{

public:
	gl_texture_1d_array() = delete;
	gl_texture_1d_array(const gl_texture_1d_array_descriptor& descriptor) :
		gl_texture(gl_texture_type::TEXTURE_1D_ARRAY),
		_descriptor(descriptor)
	{
		glTextureStorage2D(
			_handle,
			_descriptor.mipmaps_count, static_cast<GLenum>(_descriptor.pixel_format),
			_descriptor.length, // 2d width
			_descriptor.elements_count // 2d height
		);
	}

	~gl_texture_1d_array() = default;

private:

	gl_texture_1d_array_descriptor _descriptor;

public:

	gl_texture_1d_array_descriptor get_descriptor() const { return _descriptor; }
	
	void bind(std::uint32_t unit) override;

	void unbind() override;

public:

	void fill(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t x_offset, const void* data)
	{
		if (nullptr || 
			element_index < 0 || element_index >= _descriptor.elements_count ||
			mipmap_index < 0 || mipmap_index >= _descriptor.mipmaps_count ||
			x_offset < 0 || x_offset >= _descriptor.length
			) return;

		glTexSubImage2D(
			GL_TEXTURE_1D_ARRAY, 
			mipmap_index, x_offset, 0, _descriptor.length,
			element_index, 
			GL_RGBA, GL_UNSIGNED_BYTE,
			data
		);
	}

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_1D_ARRAY, _handle);
		glGenerateMipmap(GL_TEXTURE_1D_ARRAY);
		glBindTexture(GL_TEXTURE_1D_ARRAY, 0);
	}

};

#endif


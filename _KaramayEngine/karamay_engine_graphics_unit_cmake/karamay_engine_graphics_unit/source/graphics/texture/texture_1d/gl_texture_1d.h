#ifndef H_GL_TEXTURE_1D
#define H_GL_TEXTURE_1D
#include "graphics/texture/base/gl_texture.h"

struct gl_texture_1d_descriptor
{
	std::int32_t length; // how many pixels
	gl_texture_pixel_format pixel_format; // how to combine a pixel
	std::int32_t mipmaps_count; // how many mipmaps

	gl_texture_1d_descriptor(std::int32_t _length, std::int32_t _mipmaps_count, gl_texture_pixel_format _pixel_format) :
		length(_length),
		mipmaps_count(_mipmaps_count),
		pixel_format(_pixel_format)
	{}
	gl_texture_1d_descriptor(std::int32_t _length, gl_texture_pixel_format _pixel_format) :
		length(_length),
		mipmaps_count(1),
		pixel_format(_pixel_format)
	{}

	gl_texture_1d_descriptor() = delete;
	gl_texture_1d_descriptor(const gl_texture_1d_descriptor&) = default;
	gl_texture_1d_descriptor& operator=(const gl_texture_1d_descriptor&) = default;

	~gl_texture_1d_descriptor() = default;
};

class gl_texture_1d final : public gl_texture
{
public:

	gl_texture_1d() = delete;
	gl_texture_1d(const gl_texture_1d_descriptor& descriptor) :
		gl_texture(gl_texture_type::TEXTURE_1D),
		_descriptor(descriptor)
	{
		glTextureStorage1D(
			_handle, 
			descriptor.mipmaps_count, 
			static_cast<GLenum>(descriptor.pixel_format),
			descriptor.length
		);
	}

	~gl_texture_1d() override = default;
	
private:

	gl_texture_1d_descriptor _descriptor;

public:

	gl_texture_1d_descriptor get_descriptor() const { return _descriptor; }

	/*
	* you can fill the base mipmap
	*/
	void fill(std::int32_t mipmap_index, std::int32_t x_offset, const void* data)
	{
#ifdef _RELEASE
		if (mipmap_index < 0 || mipmap_index > _descriptor.mipmaps_count) return;
#endif

#ifdef _DEBUG

#endif
		glTextureSubImage1D(_handle, mipmap_index, 
			x_offset, _descriptor.length, 
			GL_RGBA, GL_UNSIGNED_BYTE, data
		);
	}

	/*
	* generate all rest mipmaps according to base mipmap, if you have manually filled any mipmaps, this action will overwrite them
	*/
	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_1D, _handle);
		glGenerateMipmap(GL_TEXTURE_1D);
		glBindTexture(GL_TEXTURE_1D, 0);
	}

	void clear(std::int32_t x_offset, std::int32_t width, const void* data, GLenum format, GLenum type, int mipmap_index = 0)
	{
		if (!data) return;
		glClearTexSubImage(_handle, mipmap_index, x_offset, 0, 0, width, 0, 0, format, type, data);
	}

	void invalidate_mipmap(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t width)
	{
		glInvalidateTexSubImage(_handle, mipmap_index, x_offset, 0, 0, width, 0, 0);
	}

	void* fetch_pixels(GLuint mipmap_index, GLenum format, GLenum type)
	{
		void* pixels = nullptr;
		glGetTexImage(GL_TEXTURE_1D, mipmap_index, format, type, pixels);
		return pixels;
	}

	std::int32_t get_pixels_count() const { return _descriptor.length; }
	
public:

	void bind(std::uint32_t unit)
	{
		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(GL_TEXTURE_1D, _handle);
		
	}

	void unbind();

};

#endif


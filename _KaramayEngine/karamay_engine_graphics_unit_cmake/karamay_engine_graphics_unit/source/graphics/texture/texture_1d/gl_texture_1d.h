#ifndef H_GL_TEXTURE_1D
#define H_GL_TEXTURE_1D

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_1d_descriptor
{
	std::int32_t length; // how many pixels
	std::int32_t mipmaps_count; // how many mipmaps
	gl_texture_enum::internal_format internal_format; // how to combine a pixel
};

class gl_texture_1d final : public gl_texture
{
public:

	explicit gl_texture_1d(const gl_texture_1d_descriptor& descriptor) :
		_descriptor(descriptor)
	{
		glCreateTextures(GL_TEXTURE_1D, 1, &_handle);
		glTextureStorage1D(_handle, descriptor.mipmaps_count, static_cast<GLenum>(descriptor.internal_format), descriptor.length);
	}

	virtual ~gl_texture_1d();
	
private:

	gl_texture_1d_descriptor _descriptor;

public:

	/*
	* you can fill the base mipmap
	*/
	void fill(std::int32_t mipmap_index, std::int32_t x_offset, const void* data)
	{
		glBindTexture(GL_TEXTURE_1D, _handle);
		glTexSubImage1D(GL_TEXTURE_1D, mipmap_index, x_offset, _descriptor.length, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glBindTexture(GL_TEXTURE_1D, 0);
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

	void* fetch_pixels(GLuint mipmap_index, GLenum format, GLenum type);

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


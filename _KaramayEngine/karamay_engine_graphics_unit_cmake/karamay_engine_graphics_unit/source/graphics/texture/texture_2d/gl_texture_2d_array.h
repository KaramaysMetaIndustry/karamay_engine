#ifndef H_GL_TEXTURE_2D_ARRAY
#define H_GL_TEXTURE_2D_ARRAY

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_2d_array_descriptor
{
	std::uint32_t elements_count;
	std::uint32_t width, height;
	std::uint32_t mipmaps_count;
	gl_texture_pixel_format format;
};

class gl_texture_2d_array final : public gl_texture
{
public:

	explicit gl_texture_2d_array(const gl_texture_2d_array_descriptor& descriptor) : 
		_descriptor(descriptor)
	{
		_allocate();
	}

	virtual ~gl_texture_2d_array();

private:
	
	gl_texture_2d_array_descriptor _descriptor;

	void _allocate()
	{
		glCreateTextures(GL_TEXTURE_2D_ARRAY, 1, &_handle);
		glTextureStorage3D(_handle, 
			_descriptor.mipmaps_count, static_cast<GLenum>(_descriptor.format), 
			_descriptor.width, _descriptor.height,
			_descriptor.elements_count
		);
	}

public:

	void fill(std::int32_t element_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, const void*data)
	{
		std::int32_t _width = 0;
		std::int32_t _height = 0;
		glTexSubImage3D(
			GL_TEXTURE_2D_ARRAY, 
			mipmap_index, x_offset, y_offset, 
			element_index, _width, _height, 1,
			static_cast<GLenum>(_descriptor.format), type, 
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
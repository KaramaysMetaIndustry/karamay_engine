#ifndef H_GL_TEXTURE_3D
#define H_GL_TEXTURE_3D

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_3d_descriptor
{
	std::int32_t width, height, depth;
	std::int32_t mipmaps_count;
	gl_texture_pixel_format format;
};

class gl_texture_3d final: public gl_texture
{
public:

	explicit gl_texture_3d(const gl_texture_3d_descriptor& descriptor) :
		_descriptor(descriptor)
	{
		glCreateTextures(GL_TEXTURE_3D, 1, &_handle);
		glTextureStorage3D(_handle, _descriptor.mipmaps_count, static_cast<GLenum>(_descriptor.format), _descriptor.width, _descriptor.height, _descriptor.depth);
	}

	virtual ~gl_texture_3d();

private:

	gl_texture_3d_descriptor _descriptor;

public:

	void fill(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::int32_t z_offset, const void* data)
	{
		glTexSubImage3D(
			GL_TEXTURE_3D, 
			mipmap_index, x_offset, y_offset, z_offset, 
			width, height, depth, format, type, data
		);
	}

	void bind(std::uint32_t unit);

	void unbind();

};

#endif


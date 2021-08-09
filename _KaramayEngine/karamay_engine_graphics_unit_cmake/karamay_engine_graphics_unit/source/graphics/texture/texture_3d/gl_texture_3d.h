#ifndef H_GL_TEXTURE_3D
#define H_GL_TEXTURE_3D

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_3d_descriptor
{
	std::int32_t width, height, depth;
	std::int32_t mipmaps_count;
	gl_texture_pixel_format pixel_format;

	gl_texture_3d_descriptor(std::int32_t _width, std::int32_t _height, std::int32_t _depth, gl_texture_pixel_format  _pixel_format, std::int32_t _mipmaps_count) :
		width(_width), height(_height), depth(_depth),
		mipmaps_count(_mipmaps_count),
		pixel_format(_pixel_format)
	{}

	gl_texture_3d_descriptor(std::int32_t _width, std::int32_t _height, std::int32_t _depth, gl_texture_pixel_format _pixel_format) :
		width(_width), height(_height), depth(_depth),
		mipmaps_count(1),
		pixel_format(_pixel_format)
	{}

};

class gl_texture_3d final: public gl_texture
{
public:

	explicit gl_texture_3d(const gl_texture_3d_descriptor& descriptor) :
		_descriptor(descriptor)
	{
		glCreateTextures(GL_TEXTURE_3D, 1, &_handle);
		glTextureStorage3D(
			_handle, 
			_descriptor.mipmaps_count, 
			static_cast<GLenum>(_descriptor.pixel_format), 
			_descriptor.width, _descriptor.height, _descriptor.depth
		);
	}

	virtual ~gl_texture_3d()
	{}

private:

	gl_texture_3d_descriptor _descriptor;

public:

	gl_texture_3d_descriptor get_descriptor() const { return _descriptor; }

	void fill(std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, std::int32_t z_offset, const void* data)
	{
		glBindTexture(GL_TEXTURE_3D, _handle);
		glTexSubImage3D(
			GL_TEXTURE_3D, 
			mipmap_index, x_offset, y_offset, z_offset, 
			width, height, depth, format, type, data
		);
		glBindTexture(GL_TEXTURE_3D, _handle);
	}

	void bind(std::uint32_t unit);

	void unbind();

};

#endif


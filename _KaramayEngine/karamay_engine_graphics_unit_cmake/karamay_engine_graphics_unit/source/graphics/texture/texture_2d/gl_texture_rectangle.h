#ifndef H_GL_TEXTURE_RECTANGLE
#define H_GL_TEXTURE_RECTANGLE

#include "graphics/texture/base/gl_texture.h"


struct gl_texture_rectangle_descriptor
{
	std::int32_t mipmaps_count;
	std::int32_t width, height;
	gl_texture_pixel_format pixel_format;

};

class gl_texture_rectangle final : public gl_texture
{
public:
	
	explicit gl_texture_rectangle(const gl_texture_rectangle_descriptor& descriptor) :
		_descriptor(descriptor)
	{
		glCreateTextures(GL_TEXTURE_RECTANGLE, 1, &_handle);
		glTextureStorage2D(_handle, 
			_descriptor.mipmaps_count, 
			static_cast<GLenum>(_descriptor.pixel_format),
			_descriptor.width, 
			_descriptor.height
		);
	}

	gl_texture_rectangle();
	
	~gl_texture_rectangle();

private:

	gl_texture_rectangle_descriptor _descriptor;

public:

	void fill_base_sub_mipmap(GLenum format, GLenum type, const void* pixels, int x_offset, int y_offset, int width, int height)
	{
		glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, x_offset, y_offset, width, height, format, type, pixels);
	}

	void bind() override
	{
		glActiveTexture(GL_TEXTURE0 + 0);
		glBindTexture(GL_TEXTURE_2D, _handle);
	}

	void unbind() override
	{}

};

#endif
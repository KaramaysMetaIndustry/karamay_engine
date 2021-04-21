#pragma once
#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_rectangle final : public gl_texture_base
{
public:
	void allocate(GLenum internal_format, int width, int height)
	{
		glTexStorage2D(GL_TEXTURE_RECTANGLE, 1, internal_format, width, height);
	}

	void fill_base_mipmap(GLenum format, GLenum type, const void* pixels)
	{
		fill_base_sub_mipmap(format, type, pixels, 0, 0, _width, _height);
	}
	void fill_base_sub_mipmap(GLenum format, GLenum type, const void* pixels, int x_offset, int y_offset, int width, int height)
	{
		glTexSubImage2D(GL_TEXTURE_RECTANGLE, 0, x_offset, y_offset, width, height, format, type, pixels);
	}


private:
	int _width, _height;

public:
	gl_texture_rectangle();
	virtual ~gl_texture_rectangle();  
};


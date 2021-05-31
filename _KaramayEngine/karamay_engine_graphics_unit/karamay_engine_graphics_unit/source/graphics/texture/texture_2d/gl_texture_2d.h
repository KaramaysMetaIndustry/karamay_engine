#pragma once
#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_2d final : public gl_texture_base
{
public:
	
	gl_texture_2d();
	
	virtual ~gl_texture_2d();

private:
	
	int _width, _height;

	int _internal_format;

	int _mipmaps_num;

public:
	
	void allocate(gl_texture_enum::internal_format internal_format, std::int32_t width, std::int32_t height, int mipmaps_num)
	{
		glTextureStorage2D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width, height);
	}

	void fill(int width, int height, std::uint32_t format, const void* pixels)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _handle);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);
	}


public:

	void fill_base_mipmap(GLenum format, GLenum type, const void* data);
	
	void fill_miniature_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index);

	void fill_base_sub_mipmap(GLenum format, GLenum type, const void* data, int x_offset, int y_offset, int width, int height);
	
	void fill_miniature_sub_mipmap(GLenum format, GLenum type, const void* data, int mipmap_index, int x_offset, int y_offset, int width, int height);
	
	void fill_miniature_mipmaps();

	void bind(std::uint32_t unit);
	
	void unbind();

public:

	std::uint32_t get_unit() { return 0; }

};

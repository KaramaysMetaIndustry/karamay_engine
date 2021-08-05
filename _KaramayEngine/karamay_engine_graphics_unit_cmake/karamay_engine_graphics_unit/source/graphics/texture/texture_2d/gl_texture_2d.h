#ifndef H_GL_TEXTURE_2D
#define H_GL_TEXTURE_2D

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_2d_descriptor
{
	std::int32_t width, height;
	std::int32_t mipmaps_count;
	gl_texture_enum::internal_format internal_format;
};

class gl_texture_2d final : public gl_texture_base
{
public:
	
	explicit gl_texture_2d(const gl_texture_2d_descriptor& descriptor)
	{
		_allocate(descriptor.internal_format, descriptor.width, descriptor.height, descriptor.mipmaps_count);
	}
	
	virtual ~gl_texture_2d();

private:

	gl_texture_2d_descriptor _descriptor;
	
	void _allocate(gl_texture_enum::internal_format internal_format, std::int32_t width, std::int32_t height, int mipmaps_num)
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &_handle);
		glTextureStorage2D(_handle, mipmaps_num, static_cast<GLenum>(internal_format), width, height);
	}

public:

	void fill(int width, int height, std::uint32_t format, const void* pixels)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, _handle);
		//
		/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);*/
		//
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

#endif

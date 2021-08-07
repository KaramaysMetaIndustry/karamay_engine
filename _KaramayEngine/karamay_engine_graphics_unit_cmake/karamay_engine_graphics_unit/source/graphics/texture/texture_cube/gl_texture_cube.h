#ifndef H_GL_TEXTURE_CUBE
#define H_GL_TEXTURE_CUBE

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_cube_descriptor
{
	std::int32_t mipmaps_count;
	std::int32_t width;
	gl_texture_pixel_format format;
};

class gl_texture_cube final : public gl_texture
{
public:

	explicit gl_texture_cube(const gl_texture_cube_descriptor& descriptor) :
		_descriptor(descriptor)
	{
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &_handle);
		glTextureStorage3D(
			GL_TEXTURE_CUBE_MAP, 
			_descriptor.mipmaps_count, 
			static_cast<GLenum>(_descriptor.format), _descriptor.face_width, _descriptor.face_width, 
			6
		);
	}

	virtual ~gl_texture_cube();

private:

	gl_texture_cube_descriptor _descriptor;

public:

	void fill(gl_cube_face_index face_index, std::int32_t mipmap_index, std::int32_t x_offset, std::int32_t y_offset, const void* data, std::int32_t width, std::int32_t height)
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
		glTexSubImage2D(static_cast<GLenum>(face_index), mipmap_index, x_offset, y_offset, width, height, format, type, data);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void generate_mipmaps()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, _handle);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void set() {

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	void bind(std::uint32_t unit) {}

	void unbind() {}

private:
	int _width;

	int _internal_format;

	int _mipmaps_num;
};

#endif
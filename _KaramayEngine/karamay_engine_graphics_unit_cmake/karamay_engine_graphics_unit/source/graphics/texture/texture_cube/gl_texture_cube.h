#ifndef H_GL_TEXTURE_CUBE
#define H_GL_TEXTURE_CUBE

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_cube_descriptor
{
	std::int32_t width;
	gl_texture_pixel_format pixel_format;
	std::int32_t mipmaps_count;

	gl_texture_cube_descriptor(std::int32_t _width, gl_texture_pixel_format _pixel_format, std::int32_t _mipmaps_count) :
		width(_width),
		pixel_format(_pixel_format),
		mipmaps_count(_mipmaps_count)
	{}

	gl_texture_cube_descriptor(std::int32_t _width, gl_texture_pixel_format _pixel_format) :
		width(_width),
		pixel_format(_pixel_format),
		mipmaps_count(1)
	{}

	gl_texture_cube_descriptor() = delete;
	gl_texture_cube_descriptor(const gl_texture_cube_descriptor&) = default;
	gl_texture_cube_descriptor& operator=(const gl_texture_cube_descriptor&) = default;

	~gl_texture_cube_descriptor() = default;
};

class gl_texture_cube final : public gl_texture
{
public:
	gl_texture_cube() = delete;
	explicit gl_texture_cube(const gl_texture_cube_descriptor& descriptor) :
		gl_texture(gl_texture_type::TEXTURE_CUBE_MAP),
		_descriptor(descriptor)
	{
		glTextureStorage3D(_handle,
			_descriptor.mipmaps_count, 
			static_cast<GLenum>(_descriptor.pixel_format), 
			_descriptor.width, _descriptor.width, 
			6
		);
	}

	gl_texture_cube(const gl_texture_cube&) = delete;
	gl_texture_cube& operator=(const gl_texture_cube&) = delete;

	~gl_texture_cube() override = default;

private:

	gl_texture_cube_descriptor _descriptor;

public:

	gl_texture_cube_descriptor get_descriptor() const { return _descriptor; }

	void fill(
		gl_cube_face_index face_index, 
		std::int32_t mipmap_index, 
		std::int32_t x_offset, std::int32_t y_offset, 
		const void* data, std::int32_t width, std::int32_t height
	)
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
};

#endif
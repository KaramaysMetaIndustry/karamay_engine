#ifndef H_GL_TEXTURE_CUBE_ARRAY
#define H_GL_TEXTURE_CUBE_ARRAY

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_cube_array_descriptor
{
	std::int32_t elements_count;
	std::int32_t width;
	gl_texture_pixel_format pixel_format;
	std::int32_t mipmaps_count;

	gl_texture_cube_array_descriptor(std::int32_t _elements_count, std::int32_t _width, gl_texture_pixel_format _pixel_format, std::int32_t _mipmaps_count) :
		elements_count(_elements_count),
		width(_width),
		pixel_format(_pixel_format),
		mipmaps_count(_mipmaps_count)
	{}

	gl_texture_cube_array_descriptor(std::int32_t _elements_count, std::int32_t _width, gl_texture_pixel_format _pixel_format) :
		elements_count(_elements_count),
		width(_width),
		pixel_format(_pixel_format),
		mipmaps_count(1)
	{}

	gl_texture_cube_array_descriptor() = delete;
	gl_texture_cube_array_descriptor(const gl_texture_cube_array_descriptor&) = default;
	gl_texture_cube_array_descriptor& operator=(const gl_texture_cube_array_descriptor&) = default;

	~gl_texture_cube_array_descriptor() = default;
};

class gl_texture_cube_array final : public gl_texture
{
public:

	explicit gl_texture_cube_array(const gl_texture_cube_array_descriptor& descriptor) :
		_descriptor(descriptor)
	{
		glCreateTextures(GL_TEXTURE_CUBE_MAP_ARRAY, 1, &_handle);
		glTextureStorage3D(
			_handle, 
			_descriptor.mipmaps_count, 
			static_cast<GLenum>(_descriptor.pixel_format), 
			_descriptor.width, _descriptor.width,
			_descriptor.elements_count * 6
		);
	}

	gl_texture_cube_array() = delete;
	gl_texture_cube_array(const gl_texture_cube_array&) = delete;
	gl_texture_cube_array& operator=(const gl_texture_cube_array&) = delete;

	~gl_texture_cube_array() override = default;

private:

	gl_texture_cube_array_descriptor _descriptor;

public:

	void fill(
		std::int32_t element_index, 
		gl_cube_face_index face_index, 
		std::int32_t mipmap_index, 
		std::int32_t x_offset, std::int32_t y_offset, 
		const void* data, std::int32_t width, std::int32_t height
	)
	{
		glTexSubImage3D(
			static_cast<GLenum>(face_index), 
			mipmap_index, x_offset, y_offset, 0, 
			width, height, (element_index + 1) * 6 - 1, format, type, data
		);
	}

	void bind(std::uint32_t unit) {}

	void unbind() {}

};

#endif


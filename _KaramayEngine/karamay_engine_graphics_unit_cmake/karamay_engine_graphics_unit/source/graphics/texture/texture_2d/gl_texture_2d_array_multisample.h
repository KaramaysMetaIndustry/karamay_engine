#ifndef H_GL_TEXTURE_2D_ARRAY_MULTISAMPLE
#define H_GL_TEXTURE_2D_ARRAY_MULTISAMPLE

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_2d_array_multisample_descriptor
{
	std::int32_t elements_count;
	std::int32_t samples_count;
	std::int32_t width, height;
	gl_texture_pixel_format pixel_format;
	bool fixed_sample_location;

	gl_texture_2d_array_multisample_descriptor(
		std::int32_t _elements_count, 
		std::int32_t _samples_count, 
		std::int32_t _width, std::int32_t _height, 
		gl_texture_pixel_format _pixel_format, 
		bool _fixed_sample_location
	) :
		elements_count(_elements_count),
		samples_count(_samples_count),
		width(_width), height(_height),
		pixel_format(_pixel_format),
		fixed_sample_location(_fixed_sample_location)
	{}

	gl_texture_2d_array_multisample_descriptor(
		std::int32_t _elements_count, 
		std::int32_t _samples_count, 
		std::int32_t _width, std::int32_t _height, 
		gl_texture_pixel_format _pixel_format
	) :
		elements_count(_elements_count),
		samples_count(_samples_count),
		width(_width), height(_height),
		pixel_format(_pixel_format),
		fixed_sample_location(false)
	{}

	gl_texture_2d_array_multisample_descriptor() = delete;
	gl_texture_2d_array_multisample_descriptor(const gl_texture_2d_array_multisample_descriptor&) = default;
	gl_texture_2d_array_multisample_descriptor& opeator = (const gl_texture_2d_array_multisample_descriptor&) = default;

	~gl_texture_2d_array_multisample_descriptor() = default;
};


class gl_texture_2d_array_multisample final : public gl_texture
{
public:
	
	explicit gl_texture_2d_array_multisample(const gl_texture_2d_array_multisample_descriptor& descriptor) :
		_descriptor(descriptor)
	{
		glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, 1, &_handle);
		glTextureStorage3DMultisample(_handle, 
			_descriptor.samples_count, 
			static_cast<GLenum>(_descriptor.pixel_format),
			_descriptor.width, _descriptor.height, 
			_descriptor.elements_count, 
			_descriptor.fixed_sample_location
		);
	}

	gl_texture_2d_array_multisample() = delete;
	gl_texture_2d_array_multisample(const gl_texture_2d_array_multisample&) = delete;
	gl_texture_2d_array_multisample& operator=(const gl_texture_2d_array_multisample&) = delete;
	
	virtual ~gl_texture_2d_array_multisample()
	{
		glDeleteTextures(1, &_handle);
	}

private:

	gl_texture_2d_array_multisample_descriptor _descriptor;

public:

	void fill(GLsizei Level,  GLsizei Width, GLsizei Height, GLsizei Num,GLenum Format, GLenum Type, std::vector<const void*> Datas) 
	{
		for (std::int32_t i = 0; i < Num; ++i)
		{
			glTexSubImage3D(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, Level, 0, 0, i, Width, Height, 1, Format, Type, Datas[i]);
		}
	}

	void bind(GLuint Unit);

	void unbind();

};

#endif


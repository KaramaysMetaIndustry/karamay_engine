#ifndef H_GL_TEXTURE_2D_MULTISAMPLE
#define H_GL_TEXTURE_2D_MULTISAMPLE

#include "graphics/texture/base/gl_texture.h"

struct gl_texture_2d_multisample_descriptor
{
	std::int32_t samples_count;
	std::int32_t width, height;
	gl_texture_pixel_format pixel_format;
	bool fixed_sample_location;

	gl_texture_2d_multisample_descriptor(std::int32_t _samples_count, std::int32_t _width, std::int32_t _height, gl_texture_pixel_format _pixel_format, bool _fixed_sample_location) :
		samples_count(_samples_count),
		width(_width), height(_height),
		pixel_format(_pixel_format),
		fixed_sample_location(_fixed_sample_location)
	{}

	gl_texture_2d_multisample_descriptor(std::int32_t _samples_count, std::int32_t _width, std::int32_t _height, gl_texture_pixel_format _pixel_format) :
		samples_count(_samples_count),
		width(_width), height(_height),
		pixel_format(_pixel_format),
		fixed_sample_location(false)
	{}

	gl_texture_2d_multisample_descriptor() = delete;
	gl_texture_2d_multisample_descriptor(const gl_texture_2d_multisample_descriptor&) = default;
	gl_texture_2d_multisample_descriptor& operator=(const gl_texture_2d_multisample_descriptor&) = default;
	~gl_texture_2d_multisample_descriptor() = default;
};

class gl_texture_2d_multisample : public gl_texture
{

public:

	explicit gl_texture_2d_multisample(const gl_texture_2d_multisample_descriptor& descriptor) :
		_descriptor(descriptor)
	{
		glCreateTextures(GL_TEXTURE_2D_MULTISAMPLE, 1, &_handle);
		glTextureStorage2DMultisample(_handle,
			descriptor.samples_count, 
			static_cast<GLenum>(_descriptor.pixel_format), 
			_descriptor.width, _descriptor.height, 
			_descriptor.fixed_sample_location
		);
	}

	gl_texture_2d_multisample() = delete;
	gl_texture_2d_multisample(const gl_texture_2d_multisample&) = delete;
	gl_texture_2d_multisample& operator=(const gl_texture_2d_multisample&) = delete;

	virtual ~gl_texture_2d_multisample()
	{
		glDeleteTextures(1, &_handle);
	}

private:

	gl_texture_2d_multisample_descriptor _descriptor;

public:

	void fill(int samples_num, int width, int height, GLboolean FixedSampleLocation) {
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples_num, _internal_format, width, height, FixedSampleLocation);
	}

	void bind(std::uint32_t unit);

	void unbind();

};

#endif


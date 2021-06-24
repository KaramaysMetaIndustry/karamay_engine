#pragma once
#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_2d_multisample : public gl_texture_base
{
public:
	void allocate(GLsizei Samples, GLenum InternalFormat, GLsizei Width, GLsizei Height, GLboolean fixedsamplelocation) {
		glTextureStorage2DMultisample(_handle, Samples, InternalFormat, Width, Height, fixedsamplelocation);
	}

	void fill(int samples_num, int width, int height, GLboolean FixedSampleLocation) {
		glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples_num, _internal_format, width, height, FixedSampleLocation);
	}


	void bind(std::uint32_t unit);

	void unbind();

private:
	int width, height;

	int _internal_format;

	

public:
	gl_texture_2d_multisample();
	virtual ~gl_texture_2d_multisample();
};


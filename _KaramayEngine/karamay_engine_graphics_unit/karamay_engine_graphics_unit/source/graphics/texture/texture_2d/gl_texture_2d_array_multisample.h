#pragma once
#include "graphics/texture/base/gl_texture_base.h"

class gl_multisample_texture_2d_array final : public gl_texture_base
{
public:
	
	gl_multisample_texture_2d_array();
	
	virtual ~gl_multisample_texture_2d_array();

public:
	
	void allocate(GLsizei Samples, GLenum InternalFormat, GLsizei Width, GLsizei Height, GLsizei Num, GLboolean FixedSampleLocation) {
		glTextureStorage3DMultisample(_handle, Samples, InternalFormat, Width, Height, Num, FixedSampleLocation);
	}

	void fill(GLsizei Level,  GLsizei Width, GLsizei Height, GLsizei Num,GLenum Format, GLenum Type, std::vector<const void*> Datas) {
		for (size_t i = 0; i < Num; ++i)
		{
			glTexSubImage3D(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, Level, 0, 0, i, Width, Height, 1, Format, Type, Datas[i]);
		}
	}

	void bind(GLuint Unit);

	void unbind();

};


#ifndef H_GL_TEXTURE_2D_ARRAY_MULTISAMPLE
#define H_GL_TEXTURE_2D_ARRAY_MULTISAMPLE

#include "graphics/texture/base/gl_texture_base.h"

class gl_texture_2d_array_multisample final : public gl_texture_base
{
public:
	
	gl_texture_2d_array_multisample();
	
	virtual ~gl_texture_2d_array_multisample();

public:
	
	/**
	 * @samples_num: num of samples
	 * @internal_format: internal storage format
	 * @width: 
	 * @height:
	 * @fixed_sample_location:
	 * @num:
	 */
	void allocate(std::int32_t samples_num, GLenum internal_format, std::int32_t width, std::int32_t height, std::uint8_t fixed_sample_location, std::int32_t num) {
		glTextureStorage3DMultisample(_handle, samples_num, internal_format, width, height, num, fixed_sample_location);
	}

	void fill(GLsizei Level,  GLsizei Width, GLsizei Height, GLsizei Num,GLenum Format, GLenum Type, std::vector<const void*> Datas) {
		for (std::int32_t i = 0; i < Num; ++i)
		{
			glTexSubImage3D(GL_TEXTURE_2D_MULTISAMPLE_ARRAY, Level, 0, 0, i, Width, Height, 1, Format, Type, Datas[i]);
		}
	}

	void bind(GLuint Unit);

	void unbind();

};

#endif


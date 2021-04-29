#pragma once
#include "graphics/glo/gl_object.h"

enum class e_sampler_parameter : GLenum
{
	texture_lod_bias = GL_TEXTURE_LOD_BIAS,
	
	texture_min_filter = GL_TEXTURE_MIN_FILTER,
	texture_mag_filter = GL_TEXTURE_MAG_FILTER,
	
	texture_min_lod = GL_TEXTURE_MIN_LOD,
	texture_max_lod = GL_TEXTURE_MAX_LOD,

	texture_wrap_s = GL_TEXTURE_WRAP_S,
	texture_wrap_t = GL_TEXTURE_WRAP_T,
	texture_wrap_r = GL_TEXTURE_WRAP_R,
	
	texture_border_color = GL_TEXTURE_BORDER_COLOR,
	
	texture_compare_mode = GL_TEXTURE_COMPARE_MODE,
	texture_compare_func = GL_TEXTURE_COMPARE_FUNC
};

class gl_sampler final : public gl_object
{
public:

	static std::shared_ptr<gl_sampler> construct()
	{
		return std::make_shared<gl_sampler>();
	}

	virtual ~gl_sampler();

private:
	gl_sampler() {}


public:
	void bind(unsigned int unit);

	void unbind();

	void set() {
		GLfloat bias = { 0.0 };
		glSamplerParameterf(_handle, static_cast<GLenum>(e_sampler_parameter::texture_lod_bias), bias);

	}
	
};


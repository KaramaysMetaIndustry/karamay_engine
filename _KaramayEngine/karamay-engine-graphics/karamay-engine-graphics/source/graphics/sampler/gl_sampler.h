#pragma once
#include "graphics/glo/gl_object.h"

namespace gl_sampler_enum
{
	enum class parameter : GLenum
	{
		TEXTURE_MIN_FILTER = GL_TEXTURE_MIN_FILTER,
		TEXTURE_MAG_FILTER = GL_TEXTURE_MAG_FILTER,

		TEXTURE_WRAP_S = GL_TEXTURE_WRAP_S,
		TEXTURE_WRAP_T = GL_TEXTURE_WRAP_T,
		TEXTURE_WRAP_R = GL_TEXTURE_WRAP_R,

		TEXTURE_LOD_BIAS = GL_TEXTURE_LOD_BIAS,
		TEXTURE_MIN_LOD = GL_TEXTURE_MIN_LOD,
		TEXTURE_MAX_LOD = GL_TEXTURE_MAX_LOD,

		TEXTURE_BORDER_COLOR = GL_TEXTURE_BORDER_COLOR,

		TEXTURE_COMPARE_MODE = GL_TEXTURE_COMPARE_MODE,
		TEXTURE_COMPARE_FUNC = GL_TEXTURE_COMPARE_FUNC
	};


	enum class texture_wrap_option : GLenum
	{
		CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
		CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
		MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
		REPEAT = GL_REPEAT,
		MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE
	};

	enum class texture_mag_filter : GLenum
	{
		NEAREST = GL_NEAREST,
		LINEAR = GL_LINEAR
	};

	enum class texture_min_filter : GLenum
	{
		NEAREST = GL_NEAREST,
		LINEAR = GL_LINEAR,
		NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
		NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
		LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
		LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST
	};
	
	enum class texture_compare_func : GLenum
	{
		LEQUAL = GL_LEQUAL,
		GEQUAL = GL_GEQUAL,
		LESS = GL_LESS,
		GREATER = GL_GREATER,
		EQUAL = GL_EQUAL,
		NOTEQUAL = GL_NOTEQUAL,
		ALWAYS = GL_ALWAYS,
		NEVER = GL_NEVER
	};

	enum class texture_compare_mode : GLenum
	{
		COMPARE_REF_TO_TEXTURE = GL_COMPARE_REF_TO_TEXTURE,
		NONE = GL_NONE
	};
}



class gl_sampler final : public gl_object
{
public:

	static std::shared_ptr<gl_sampler> construct()
	{
		return std::make_shared<gl_sampler>();
	}

	virtual ~gl_sampler()
	{
		glDeleteSamplers(1, &_handle);
	}

private:
	
	gl_sampler()
	{
		glCreateSamplers(1, &_handle);
	}

public:

	void bind(unsigned int unit);

	void unbind();

public:

	void set_texture_min_filter(gl_sampler_enum::texture_min_filter texture_min_filter);

	void set_texture_mag_filter(gl_sampler_enum::texture_mag_filter texture_mag_filter);

	
	void set_texture_wrap_s(gl_sampler_enum::texture_wrap_option texture_wrap_s);

	void set_texture_wrap_t(gl_sampler_enum::texture_wrap_option texture_wrap_t);

	void set_texture_wrap_r(gl_sampler_enum::texture_wrap_option texture_wrap_r);

	
	void set_texture_compare_func(gl_sampler_enum::texture_compare_func texture_compare_func);

	void set_texture_compare_mode(gl_sampler_enum::texture_compare_mode texture_compare_mode);

	
	void set_texture_border_color(glm::vec4 texture_border_color = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f));
	
	/**
	 * Specify a bias for texture sampling. 
	 * The value is clamped into [-GL_MAX_TEXTURE_LOD_BIAS, GL_MAX_TEXTURE_LOD_BIAS]
	 * Default value is 0.0f.
	 */
	void set_texture_lod_bias(std::float_t texture_lod_bias = 0.0f);
	
	/**
	 * Default value is -1000.0f
	 */
	void set_texture_min_lod(std::float_t texture_min_lod = -1000.0f);

	/**
	 * Default value is 1000.0f
	 */
	void set_texture_max_lod(std::float_t texture_max_lod = 1000.0f);

};


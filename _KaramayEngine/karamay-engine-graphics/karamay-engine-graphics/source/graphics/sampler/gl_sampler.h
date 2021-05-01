#pragma once
#include "graphics/glo/gl_object.h"

namespace gl_sampler_enum
{
	enum class parameter : GLenum
	{
		TEXTURE_LOD_BIAS = GL_TEXTURE_LOD_BIAS,

		TEXTURE_MIN_FILTER = GL_TEXTURE_MIN_FILTER,
		TEXTURE_MAG_FILTER = GL_TEXTURE_MAG_FILTER,

		TEXTURE_MIN_LOD = GL_TEXTURE_MIN_LOD,
		TEXTURE_MAX_LOD = GL_TEXTURE_MAX_LOD,

		TEXTURE_WRAP_S = GL_TEXTURE_WRAP_S,
		TEXTURE_WRAP_T = GL_TEXTURE_WRAP_T,
		TEXTURE_WRAP_R = GL_TEXTURE_WRAP_R,

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

	enum class texture_swizzle_component : GLenum
	{
		RED = GL_RED,
		GREEN = GL_GREEN,
		BLUE = GL_BLUE,
		ALPHA = GL_ALPHA,
		ZERO = GL_ZERO,
		ONE = GL_ONE
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

	enum class depth_stencil_texture_mode : GLenum
	{
		STENCIL_INDEX = GL_STENCIL_INDEX,
		DEPTH_COMPONENT = GL_DEPTH_COMPONENT
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
	
	gl_sampler() :
		_depth_stencil_texture_mode(gl_sampler_enum::depth_stencil_texture_mode::DEPTH_COMPONENT),
		_texture_base_level(0),
		_texture_border_color(glm::vec4(0.0f, 0.0f, 0.0f, 0.0f)),
		_texture_compare_func(gl_sampler_enum::texture_compare_func::ALWAYS),
		_texture_compare_mode(gl_sampler_enum::texture_compare_mode::NONE),
		_texture_lod_bias(0.0f),
		_texture_min_filter(gl_sampler_enum::texture_min_filter::NEAREST_MIPMAP_LINEAR),
		_texture_mag_filter(gl_sampler_enum::texture_mag_filter::LINEAR),
		_texture_min_lod(-1000),
		_texture_max_lod(1000),
		_texture_swizzle_r(gl_sampler_enum::texture_swizzle_component::RED),
		_texture_swizzle_g(gl_sampler_enum::texture_swizzle_component::GREEN),
		_texture_swizzle_b(gl_sampler_enum::texture_swizzle_component::BLUE),
		_texture_swizzle_a(gl_sampler_enum::texture_swizzle_component::ALPHA),
		_texture_wrap_s(gl_sampler_enum::texture_wrap_option::REPEAT),
		_texture_wrap_t(gl_sampler_enum::texture_wrap_option::REPEAT),
		_texture_wrap_r(gl_sampler_enum::texture_wrap_option::REPEAT)
	{
		glCreateSamplers(1, &_handle);
	}

	

	int _texture_base_level;

	glm::vec4 _texture_border_color;

	int _texture_lod_bias;

	int _texture_min_lod, _texture_max_lod;

	int _texture_max_level;

	gl_sampler_enum::depth_stencil_texture_mode _depth_stencil_texture_mode;

	gl_sampler_enum::texture_compare_func _texture_compare_func;

	gl_sampler_enum::texture_compare_mode _texture_compare_mode;

	gl_sampler_enum::texture_min_filter _texture_min_filter;

	gl_sampler_enum::texture_mag_filter _texture_mag_filter;

	gl_sampler_enum::texture_swizzle_component _texture_swizzle_r;

	gl_sampler_enum::texture_swizzle_component _texture_swizzle_g;
	
	gl_sampler_enum::texture_swizzle_component _texture_swizzle_b;
	
	gl_sampler_enum::texture_swizzle_component _texture_swizzle_a;

	gl_sampler_enum::texture_wrap_option _texture_wrap_t;
	
	gl_sampler_enum::texture_wrap_option _texture_wrap_r;
	
	gl_sampler_enum::texture_wrap_option _texture_wrap_s;

public:

	void bind(unsigned int unit);

	void unbind();

public:

	void set_with_default_parameters();

public:

	void set_depth_stencil_texture_mode(gl_sampler_enum::depth_stencil_texture_mode mode);

	void set_texture_base_level(unsigned int texture_base_level);

	void set_texture_border_color(glm::vec4 texture_border_color);

	void set_texture_compare_func(gl_sampler_enum::texture_compare_func texture_compare_func);

	void set_texture_compare_mode(gl_sampler_enum::texture_compare_mode texture_compare_mode);

	void set_texture_lod_bias(unsigned int texture_lod_bias);

	void set_texure_min_filter(gl_sampler_enum::texture_min_filter texture_min_filter);

	void set_texture_mag_filter(gl_sampler_enum::texture_mag_filter texture_mag_filter);

	void set_texture_min_lod(unsigned int texture_min_lod);

	void set_texture_max_lod(unsigned int texture_max_lod);

	void set_texture_max_level(unsigned int texture_max_level);

	void set_texture_swizzle_r(gl_sampler_enum::texture_swizzle_component texture_swizzle_r);

	void set_texture_swizzle_g(gl_sampler_enum::texture_swizzle_component texture_swizzle_g);

	void set_texture_swizzle_b(gl_sampler_enum::texture_swizzle_component texture_swizzle_b);

	void set_texture_swizzle_a(gl_sampler_enum::texture_swizzle_component texture_swizzle_a);

	void set_texture_swizzle_rgba(glm::ivec4 rgba);

	void set_texture_wrap_s(gl_sampler_enum::texture_wrap_option texture_wrap_s);

	void set_texture_wrap_t(gl_sampler_enum::texture_wrap_option texture_wrap_t);

	void set_texture_wrap_r(gl_sampler_enum::texture_wrap_option texture_wrap_r);
	
};


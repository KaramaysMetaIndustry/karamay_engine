#ifndef H_GL_SAMPLER
#define H_GL_SAMPLER

#include "graphics/glo/gl_object.h"
#include "public/glm.h"

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

}

enum class gl_depth_stencil_texture_mode : GLenum
{
	DEPTH_COMPONENT = GL_DEPTH_COMPONENT, // initial
	STENCIL_INDEX = GL_STENCIL_INDEX
};

enum class gl_texture_compare_func : GLenum
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

enum class gl_texture_compare_mode : GLenum
{
	COMPARE_REF_TO_TEXTURE = GL_COMPARE_REF_TO_TEXTURE,
	NONE = GL_NONE
};

enum class gl_texture_wrap_option : GLenum
{
	CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
	CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER,
	MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
	REPEAT = GL_REPEAT,
	MIRROR_CLAMP_TO_EDGE = GL_MIRROR_CLAMP_TO_EDGE
};

enum class gl_texture_mag_filter : GLenum
{
	NEAREST = GL_NEAREST,
	LINEAR = GL_LINEAR
};

enum class gl_texture_min_filter : GLenum
{
	NEAREST = GL_NEAREST,
	LINEAR = GL_LINEAR,
	NEAREST_MIPMAP_NEAREST = GL_NEAREST_MIPMAP_NEAREST,
	NEAREST_MIPMAP_LINEAR = GL_NEAREST_MIPMAP_LINEAR,
	LINEAR_MIPMAP_LINEAR = GL_LINEAR_MIPMAP_LINEAR,
	LINEAR_MIPMAP_NEAREST = GL_LINEAR_MIPMAP_NEAREST
};

enum class gl_texture_swizzle_component : GLenum
{
	RED = GL_RED,
	GREEN = GL_GREEN,
	BLUE = GL_BLUE,
	ZERO = GL_ZERO
};

struct gl_sampler_descriptor
{
	gl_depth_stencil_texture_mode  depth_stencil_texture_mode;
	std::int32_t texture_base_level; // inital 0
	glm::vec4 texture_border_color; // initial (0.0, 0.0, 0.0, 0.0)
	gl_texture_compare_func texture_compare_func; //
	gl_texture_compare_mode texture_compare_mode;// 
	std::float_t texture_lod_bias; // inital 0.0
	gl_texture_min_filter texture_min_filter; // GL_NEAREST_MIPMAP_LINEAR.
	gl_texture_mag_filter texture_mag_filter; // GL_LINEAR.
	std::float_t texture_min_lod; // initial -1000
	std::float_t texture_max_lod; // initial 1000
	std::int32_t texture_max_level; // initial 1000
	gl_texture_swizzle_component texture_swizzle_r; //RED
	gl_texture_swizzle_component texture_swizzle_g; //GREEN
	gl_texture_swizzle_component texture_swizzle_b; //BLUE
	gl_texture_swizzle_component texture_swizzle_a; // ALPHA
	gl_texture_swizzle_component texture_swizzle_rgba;
	gl_texture_wrap_option texture_wrap_s; //REPEAT
	gl_texture_wrap_option texture_wrap_t; //REPEAT
	gl_texture_wrap_option texture_wrap_r; //REPEAT

	gl_sampler_descriptor()
	{

	}

};

class gl_sampler final : public gl_object
{
public:

	explicit gl_sampler(const gl_sampler_descriptor& descriptor) :
		_descriptor(descriptor)
	{
		glCreateSamplers(1, &_handle);
		_initialize_paramters();
	}

	virtual ~gl_sampler();

private:

	gl_sampler_descriptor _descriptor;

	void _initialize_paramters()
	{
		glSamplerParameteri(_handle, GL_DEPTH_STENCIL_TEXTURE_MODE, static_cast<GLint>(_descriptor.depth_stencil_texture_mode));
		glSamplerParameteri(_handle, GL_TEXTURE_BASE_LEVEL, static_cast<GLint>(_descriptor.texture_base_level));
		glSamplerParameterfv(_handle, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(_descriptor.texture_border_color));
		glSamplerParameteri(_handle, GL_TEXTURE_COMPARE_FUNC, static_cast<GLint>(_descriptor.texture_compare_func));
		glSamplerParameteri(_handle, GL_TEXTURE_COMPARE_MODE, static_cast<GLint>(_descriptor.texture_compare_mode));
		glSamplerParameterf(_handle, GL_TEXTURE_LOD_BIAS, _descriptor.texture_lod_bias);
		glSamplerParameteri(_handle, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(_descriptor.texture_min_filter));
		glSamplerParameteri(_handle, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(_descriptor.texture_mag_filter));
		glSamplerParameterf(_handle, GL_TEXTURE_MIN_LOD, _descriptor.texture_min_lod);
		glSamplerParameterf(_handle, GL_TEXTURE_MAX_LOD, _descriptor.texture_max_lod);
		glSamplerParameteri(_handle, GL_TEXTURE_MAX_LEVEL, _descriptor.texture_max_level);
		glSamplerParameteri(_handle, GL_TEXTURE_SWIZZLE_R, static_cast<GLint>(_descriptor.texture_swizzle_r));
		glSamplerParameteri(_handle, GL_TEXTURE_SWIZZLE_G, static_cast<GLint>(_descriptor.texture_swizzle_g));
		glSamplerParameteri(_handle, GL_TEXTURE_SWIZZLE_B, static_cast<GLint>(_descriptor.texture_swizzle_b));
		glSamplerParameteri(_handle, GL_TEXTURE_SWIZZLE_A, static_cast<GLint>(_descriptor.texture_swizzle_a));
		glSamplerParameteriv(_handle, GL_TEXTURE_SWIZZLE_RGBA, glm::value_ptr(glm::ivec4()));
		glSamplerParameteri(_handle, GL_TEXTURE_WRAP_S, static_cast<GLint>(_descriptor.texture_wrap_s));
		glSamplerParameteri(_handle, GL_TEXTURE_WRAP_T, static_cast<GLint>(_descriptor.texture_wrap_t));
		glSamplerParameteri(_handle, GL_TEXTURE_WRAP_R, static_cast<GLint>(_descriptor.texture_wrap_r));
	}

public:

	void bind(std::uint32_t unit)
	{
		if (unit < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)
		{
			glBindSampler(unit, _handle);
			_unit = unit;
		}
	}

	void unbind()
	{
		glBindSampler(_unit, 0);
	}


public:

	gl_sampler_enum::texture_mag_filter get_texture_mag_filter()
	{
		GLint value = 0;
		glGetSamplerParameteriv(_handle, GL_TEXTURE_MAG_FILTER, &value);
		return static_cast<gl_sampler_enum::texture_mag_filter>(value);
	}

	gl_sampler_enum::texture_min_filter get_texture_min_filter()
	{
		GLint value = 0;
		glGetSamplerParameteriv(_handle, GL_TEXTURE_MIN_FILTER, &value);
		return static_cast<gl_sampler_enum::texture_min_filter>(value);
	}

	std::float_t get_max_lod()
	{
		GLfloat value = 0.0f;
		glGetSamplerParameterfv(_handle, GL_TEXTURE_MAX_LOD, &value);
		return static_cast<std::float_t>(value);
	}

	std::float_t get_min_lod()
	{
		GLfloat value = 0.0f;
		glGetSamplerParameterfv(_handle, GL_TEXTURE_MIN_LOD, &value);
		return static_cast<std::float_t>(value);
	}

	gl_sampler_enum::texture_wrap_option get_texture_wrap_s()
	{
		GLint value = 0;
		glGetSamplerParameteriv(_handle, GL_TEXTURE_WRAP_S, &value);
		return static_cast<gl_sampler_enum::texture_wrap_option>(value);
	}

	gl_sampler_enum::texture_wrap_option get_texture_wrap_t()
	{
		GLint value = 0;
		glGetSamplerParameteriv(_handle, GL_TEXTURE_WRAP_T, &value);
		return static_cast<gl_sampler_enum::texture_wrap_option>(value);
	}
	
	gl_sampler_enum::texture_wrap_option get_texture_wrap_r()
	{
		GLint value = 0;
		glGetSamplerParameteriv(_handle, GL_TEXTURE_WRAP_R, &value);
		return static_cast<gl_sampler_enum::texture_wrap_option>(value);
	}

	glm::vec4 get_texture_border_color()
	{
		GLfloat* values = nullptr;
		glGetSamplerParameterfv(_handle, GL_TEXTURE_BORDER_COLOR, values);
		return glm::vec4();
	}

	gl_sampler_enum::texture_compare_mode get_texture_compare_mode()
	{
		GLint value = 0;
		glGetSamplerParameteriv(_handle, GL_TEXTURE_COMPARE_MODE, &value);
		return static_cast<gl_sampler_enum::texture_compare_mode>(value);
	}

	gl_sampler_enum::texture_compare_func get_texture_compare_func()
	{
		GLint value = 0;
		glGetSamplerParameteriv(_handle, GL_TEXTURE_COMPARE_FUNC, &value);
		return static_cast<gl_sampler_enum::texture_compare_func>(value);
	}

private:
	
	bool is_sampler_object() const
	{
		return glIsSampler(_handle) == GL_TRUE ? true : false;
	}
};

#endif


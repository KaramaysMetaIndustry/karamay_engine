#include "gl_sampler.h"

void gl_sampler::bind(unsigned int unit)
{
	if (!(unit >= 0 && unit < GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS)) return;

	glBindSampler(unit, _handle);
}

void gl_sampler::unbind()
{

}

void gl_sampler::set_with_default_parameters()
{
}

void gl_sampler::set_depth_stencil_texture_mode(gl_sampler_enum::depth_stencil_texture_mode mode)
{
	glSamplerParameteri(_handle, GL_DEPTH_STENCIL_TEXTURE_MODE, static_cast<GLint>(mode));
}

void gl_sampler::set_texture_base_level(unsigned int texture_base_level)
{
	glSamplerParameteri(_handle, GL_TEXTURE_BASE_LEVEL, texture_base_level);
}

void gl_sampler::set_texture_border_color(glm::vec4 texture_border_color)
{
	glSamplerParameterfv(_handle, GL_TEXTURE_BORDER_COLOR, glm::value_ptr(texture_border_color));
}

void gl_sampler::set_texture_compare_func(gl_sampler_enum::texture_compare_func texture_compare_func)
{
	glSamplerParameteri(_handle, GL_TEXTURE_COMPARE_FUNC, static_cast<GLint>(texture_compare_func));
}

void gl_sampler::set_texture_compare_mode(gl_sampler_enum::texture_compare_mode texture_compare_mode)
{
	glSamplerParameteri(_handle, GL_TEXTURE_COMPARE_MODE, static_cast<GLint>(texture_compare_mode));
}

void gl_sampler::set_texture_lod_bias(unsigned int texture_lod_bias)
{
	glSamplerParameterf(_handle, GL_TEXTURE_LOD_BIAS, texture_lod_bias);
}

void gl_sampler::set_texure_min_filter(gl_sampler_enum::texture_min_filter texture_min_filter)
{
	glSamplerParameteri(_handle, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(texture_min_filter));
}

void gl_sampler::set_texture_mag_filter(gl_sampler_enum::texture_mag_filter texture_mag_filter)
{
	glSamplerParameteri(_handle, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(texture_mag_filter));
}

void gl_sampler::set_texture_min_lod(unsigned int texture_min_lod)
{
	glSamplerParameteri(_handle, GL_TEXTURE_MIN_LOD, texture_min_lod);
}

void gl_sampler::set_texture_max_lod(unsigned int texture_max_lod)
{
	glSamplerParameteri(_handle, GL_TEXTURE_MAX_LOD, texture_max_lod);
}

void gl_sampler::set_texture_max_level(unsigned int texture_max_level)
{
	glSamplerParameteri(_handle, GL_TEXTURE_MAX_LEVEL, texture_max_level);
}

void gl_sampler::set_texture_swizzle_r(gl_sampler_enum::texture_swizzle_component texture_swizzle_r)
{
	glSamplerParameteri(_handle, GL_TEXTURE_SWIZZLE_R, static_cast<GLint>(texture_swizzle_r));
}

void gl_sampler::set_texture_swizzle_g(gl_sampler_enum::texture_swizzle_component texture_swizzle_g)
{
	glSamplerParameteri(_handle, GL_TEXTURE_SWIZZLE_G, static_cast<GLint>(texture_swizzle_g));
}

void gl_sampler::set_texture_swizzle_b(gl_sampler_enum::texture_swizzle_component texture_swizzle_b)
{
	glSamplerParameteri(_handle, GL_TEXTURE_SWIZZLE_B, static_cast<GLint>(texture_swizzle_b));
}

void gl_sampler::set_texture_swizzle_a(gl_sampler_enum::texture_swizzle_component texture_swizzle_a)
{
	glSamplerParameteri(_handle, GL_TEXTURE_SWIZZLE_A, static_cast<GLint>(texture_swizzle_a));
}

void gl_sampler::set_texture_swizzle_rgba(glm::ivec4 rgba)
{
	glSamplerParameteriv(_handle, GL_TEXTURE_SWIZZLE_RGBA, glm::value_ptr(rgba));
}

void gl_sampler::set_texture_wrap_s(gl_sampler_enum::texture_wrap_option texture_wrap_s)
{
	glSamplerParameteri(_handle, GL_TEXTURE_WRAP_S, static_cast<GLint>(texture_wrap_s));
}

void gl_sampler::set_texture_wrap_t(gl_sampler_enum::texture_wrap_option texture_wrap_t)
{
	glSamplerParameteri(_handle, GL_TEXTURE_WRAP_T, static_cast<GLint>(texture_wrap_t));
}

void gl_sampler::set_texture_wrap_r(gl_sampler_enum::texture_wrap_option texture_wrap_r)
{
	glSamplerParameteri(_handle, GL_TEXTURE_WRAP_R, static_cast<GLint>(texture_wrap_r));
}

gl_sampler::gl_sampler()
{
	glCreateSamplers(1, &_handle);
}

gl_sampler::~gl_sampler()
{
	glDeleteSamplers(1, &_handle);
}

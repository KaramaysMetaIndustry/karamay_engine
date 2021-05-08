#include "gl_sampler.h"

gl_sampler::gl_sampler()
{
	glCreateSamplers(1, &_handle);
}

gl_sampler::~gl_sampler()
{
	glDeleteSamplers(1, &_handle);
}

void gl_sampler::bind(std::uint32_t texture_unit)
{
	if (texture_unit > GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS) return;

	glBindSampler(texture_unit, _handle);
}

void gl_sampler::unbind()
{
	glBindSampler(0, _handle);
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

void gl_sampler::set_texture_lod_bias(std::float_t texture_lod_bias)
{
	glSamplerParameterf(_handle, GL_TEXTURE_LOD_BIAS, texture_lod_bias);
}

void gl_sampler::set_texture_min_filter(gl_sampler_enum::texture_min_filter texture_min_filter)
{
	glSamplerParameteri(_handle, GL_TEXTURE_MIN_FILTER, static_cast<GLint>(texture_min_filter));
}

void gl_sampler::set_texture_mag_filter(gl_sampler_enum::texture_mag_filter texture_mag_filter)
{
	glSamplerParameteri(_handle, GL_TEXTURE_MAG_FILTER, static_cast<GLint>(texture_mag_filter));
}

void gl_sampler::set_texture_min_lod(std::float_t texture_min_lod)
{
	glSamplerParameterf(_handle, GL_TEXTURE_MIN_LOD, texture_min_lod);
}

void gl_sampler::set_texture_max_lod(std::float_t texture_max_lod)
{
	glSamplerParameterf(_handle, GL_TEXTURE_MAX_LOD, texture_max_lod);
}

void gl_sampler::set_texture_wrap_s(gl_sampler_enum::texture_wrap_option texture_wrap_option)
{
	glSamplerParameteri(_handle, GL_TEXTURE_WRAP_S, static_cast<GLint>(texture_wrap_option));
}

void gl_sampler::set_texture_wrap_t(gl_sampler_enum::texture_wrap_option texture_wrap_option)
{
	glSamplerParameteri(_handle, GL_TEXTURE_WRAP_T, static_cast<GLint>(texture_wrap_option));
}

void gl_sampler::set_texture_wrap_r(gl_sampler_enum::texture_wrap_option texture_wrap_option)
{
	glSamplerParameteri(_handle, GL_TEXTURE_WRAP_R, static_cast<GLint>(texture_wrap_option));
}
#include "gl_texture_base.h"

gl_texture_base::gl_texture_base()
{
}

void gl_texture_base::set_sampler(std::shared_ptr<class gl_sampler> sampler)
{
	_sampler = sampler;
}

void gl_texture_base::set_depth_stencil_texture_mode(gl_texture_enum::type texture_type, gl_texture_enum::depth_stencil_texture_mode depth_stencil_texture_mode)
{
	glTexParameteri(static_cast<GLenum>(texture_type),
		static_cast<GLenum>(gl_texture_enum::parameter::DEPTH_STENCIL_TEXTURE_MODE),
		static_cast<GLint>(depth_stencil_texture_mode));
}

void gl_texture_base::set_texture_base_level(gl_texture_enum::type texture_type, std::uint32_t texture_base_level)
{
	glTexParameteri(static_cast<GLenum>(texture_type),
		static_cast<GLenum>(gl_texture_enum::parameter::TEXTURE_BASE_LEVEL),
		static_cast<GLint>(texture_base_level));
}

void gl_texture_base::set_texture_max_level(gl_texture_enum::type texture_type, std::uint32_t texture_max_level)
{
	glTexParameteri(static_cast<GLenum>(texture_type),
		static_cast<GLenum>(gl_texture_enum::parameter::TEXTURE_MAX_LEVEL),
		static_cast<GLint>(texture_max_level));
}

void gl_texture_base::set_texture_swizzle_rgba(gl_texture_enum::type texture_type, std::array<gl_texture_enum::texture_swizzle_component, 4> texture_swizzle_rgba)
{
	std::array<GLint, 4> data;
	for (int i = 0; i < 4; ++i)
	{
		data[i] = static_cast<GLint>(texture_swizzle_rgba[i]);
	}

	glTexParameteriv(static_cast<GLenum>(texture_type),
		static_cast<GLenum>(gl_texture_enum::parameter::TEXTURE_SWIZZLE_RGBA),
		data.data());
}

gl_texture_base::~gl_texture_base()
{
}

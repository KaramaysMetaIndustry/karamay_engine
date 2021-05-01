// karamay-engine-graphics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "graphics/texture/gl_texture.h"
#include "graphics/buffer/gl_buffer.h"
#include "graphics/program_pipeline/gl_program_pipeline.h"
#include "graphics/framebuffer/gl_framebuffer.h"
#include "graphics/renderbuffer/gl_renderbuffer.h"
#include "graphics/renderbuffer/gl_multisample_renderbuffer.h"
#include "graphics/sampler/gl_sampler.h"
#include "graphics/transform_feedback/gl_transform_feedback.h"

int main()
{
   
	auto framebuffer = gl_framebuffer::construct();
	if (framebuffer.get()) {
		framebuffer->attach_color_buffer_2d(0, std::make_shared<gl_texture_2d>(), 0);
		framebuffer->attach_color_buffer_2d(1, std::make_shared<gl_texture_2d>(), 0);
		framebuffer->attach_color_buffer_2d(2, std::make_shared<gl_texture_2d>(), 0);
		framebuffer->attach_depth_stencil_buffer_2d(std::make_shared<gl_texture_2d>(), 0);

		framebuffer->bind();
		framebuffer->unbind();
	}


	auto pipeline = gl_program_pipeline::construct();



	auto texture_1d = gl_texture_1d::construct();
	//texture_1d->allocate(gl_texture_internal_format::R16, 100, 1);


	auto renderbuffer = gl_renderbuffer::construct();
	renderbuffer->allocate(gl_renderbuffer_enum::internal_format::NONE, 100, 100);
	renderbuffer->bind();
	renderbuffer->unbind();
	const auto handle = renderbuffer->get_handle();

	auto multisample_renderbuffer = gl_multisample_renderbuffer::construct();
	multisample_renderbuffer->allocate(10, gl_multisample_renderbuffer_enum::internal_format::NONE, 200, 200);
	multisample_renderbuffer->bind();
	multisample_renderbuffer->unbind();


	auto sampler = gl_sampler::construct();
	sampler->set_depth_stencil_texture_mode(gl_sampler_enum::depth_stencil_texture_mode::STENCIL_INDEX);
	sampler->set_texture_base_level(100);
	sampler->set_texture_mag_filter(gl_sampler_enum::texture_mag_filter::NEAREST);
	sampler->set_texture_compare_mode(gl_sampler_enum::texture_compare_mode::COMPARE_REF_TO_TEXTURE);

	texture_1d->add_sampler(sampler);


	auto transform_feedback = gl_transform_feedback::construct();
	transform_feedback->bind();
	transform_feedback->unbind();
	
}

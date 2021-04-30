// karamay-engine-graphics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "graphics/texture/gl_texture.h"
#include "graphics/buffer/gl_buffer.h"
#include "graphics/program_pipeline/gl_program_pipeline.h"
#include "graphics/framebuffer/gl_framebuffer.h"

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
	

}

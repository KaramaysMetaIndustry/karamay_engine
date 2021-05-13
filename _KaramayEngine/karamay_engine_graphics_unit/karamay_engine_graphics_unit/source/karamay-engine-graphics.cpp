// karamay-engine-graphics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "graphics/texture/gl_texture.h"
#include "graphics/buffer/gl_buffer.h"
#include "graphics/program/gl_program.h"
#include "graphics/program_pipeline/gl_program_pipeline.h"
#include "graphics/framebuffer/gl_framebuffer.h"
#include "graphics/renderbuffer/gl_renderbuffer.h"
#include "graphics/renderbuffer/gl_multisample_renderbuffer.h"
#include "graphics/sampler/gl_sampler.h"
#include "graphics/transform_feedback/gl_transform_feedback.h"
#include "graphics/vertex_array/gl_vertex_array.h"

int main()
{
  
	auto program = std::make_shared<gl_program>();
	auto normals = std::make_shared<gl_buffer>();
	auto positions = std::make_shared<gl_buffer>();
	auto uvs = std::make_shared<gl_buffer>();

	auto vertices = std::make_shared<gl_buffer>();

	auto instance_offsets = std::make_shared<gl_buffer>();
	auto indices = std::make_shared<gl_buffer>();


	if (program) {
		//program->set_transform_feedback_varyings();
	}

	// create buffer and associate it with initial array buffers
	auto vao = std::make_shared<gl_vertex_array>();
	if (vao) {
		vao->associate_array_buffer(vertices, 
			{ 
				{0, 3, GL_FLOAT, 0},  
				{1, 3, GL_FLOAT, 0}, 
				{2, 2, GL_FLOAT, 0} 
			}
		);
		vao->associate_array_buffer_instanced(instance_offsets, { {3, 3, GL_FLOAT, 0, 1} });
	}

	// create and associate
	auto transform_feedback = std::make_shared<gl_transform_feedback>();
	if (transform_feedback)
	{
		transform_feedback->associate_buffer(0, vertices);
	}


	// render

	if (program && vao)
	{
		
		// install program
		//program->set_uniform_1f("projection_matrix", 0.1f);
		

		// prepare vertex
		vao->bind();
		vao->enable_vertex_attributes();

		
		// call draw commands (push vertices into pipeline's vertex puller)
		glDrawArrays(0, 0, 0);



		// render commands
		vao->disable_vertex_attributes();
		vao->unbind();
	}

}

#include "gl_static_mesh_renderer.h"

struct glsl_uniform_block_Matrices
{
	glsl_vec3 position;
	glsl_vec4 color;
	glsl_mat4 porjection_mat;
};


void gl_static_mesh_renderer::assembly(gl_renderer_builder& builder)
{
	gl_graphics_pipeline_descriptor _graphics_pipeline_descriptor;
	_graphics_pipeline_descriptor.vertex_assembly.vertex_specification;
	_graphics_pipeline_descriptor.vertex_assembly.primitive_restart.enabled = true;

	auto _graphics_pipeline = builder.create_graphics_pipeline(_graphics_pipeline_descriptor);
	_graphics_pipeline->set_primitive_clipping(gl_clip_control_origin::lower_left, gl_clip_control_depth_mode::negative_one_to_one);

	_add_pass("CalculateNormals", [_graphics_pipeline]() {
		_graphics_pipeline->draw_triangles();
		});


	auto render_target = builder.create_texture_2d(1024, 2048, gl_texture_pixel_format::RGBA32F);
	if (render_target)
	{
		render_target->fill(0, 512, 1024);
	}

	glsl_sampler2D _output();
	glsl_image2D _input_positions();
}

void gl_static_mesh_renderer::render(std::float_t delta_time)
{
	// Async all commands, block main thread here
	glFlush();
}

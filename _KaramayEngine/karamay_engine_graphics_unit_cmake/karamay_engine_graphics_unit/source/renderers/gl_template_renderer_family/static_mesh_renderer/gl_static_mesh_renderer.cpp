#include "gl_static_mesh_renderer.h"

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
}

void gl_static_mesh_renderer::render(std::float_t delta_time)
{
	// Async all commands, block main thread here
	glFlush();
}

#include "gl_static_mesh_renderer.h"

void gl_static_mesh_renderer::assembly(gl_renderer_builder& builder)
{
	
}

void gl_static_mesh_renderer::render(std::float_t delta_time)
{
	// Async all commands, block main thread here
	glFlush();
}

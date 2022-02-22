#include "glsl_vertex_shader.h"

bool glsl_vertex_shader::load(const std::string& pipeline_dir)
{
	_shader = new gl_shader(
		gl_shader_type::VERTEX_SHADER,
		pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("\\") + 1) + ".vert"
	);
	return _shader->get_compile_status();
}

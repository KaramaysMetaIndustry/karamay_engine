#ifndef GLSL_VERTEX_SHADER_H
#define GLSL_VERTEX_SHADER_H
#include "glsl_shader.h"

struct glsl_vertex_attribute {};
struct glsl_instance_attribute {};

// .vert
class glsl_vertex_shader : public glsl_shader
{
public:
	glsl_vertex_shader() = default;

	glsl_vertex_shader(const glsl_vertex_shader&) = delete;
	glsl_vertex_shader& operator=(const glsl_vertex_shader&) = delete;

	~glsl_vertex_shader() = default;

public:

	bool generate_template(const std::string& pipeline_dir) override
	{
		return false;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::VERTEX_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("\\") + 1) + ".vert");
		return _shader->get_compile_status();
	}

};

class glsl_vertex_shader_template_parameters
{};

class glsl_vertex_shader_template
{

};

#endif
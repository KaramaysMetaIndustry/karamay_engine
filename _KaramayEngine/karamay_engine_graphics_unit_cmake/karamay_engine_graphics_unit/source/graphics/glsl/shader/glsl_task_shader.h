#ifndef GLSL_TASK_SHADER_H
#define GLSL_TASK_SHADER_H
#include "glsl_shader.h"

class glsl_task_shader : public glsl_shader
{
public:

	glsl_task_shader() = default;

	glsl_task_shader(const glsl_task_shader&) = delete;
	glsl_task_shader& operator=(const glsl_task_shader&) = delete;

	~glsl_task_shader() = default;

public:

	bool generate_template(const std::string& pipeline_dir) override
	{
		std::ifstream _file;
		std::string _content = "#version 460\n";
		return false;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::TASK_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("/") + 1) + ".task");
		return _shader->get_compile_status();
	}
};

class glsl_task_shader_template_parameters
{};

class glsl_task_shader_template
{};

#endif
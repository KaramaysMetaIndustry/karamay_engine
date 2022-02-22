#ifndef GLSL_TESSELLATION_CONTROL_SHADER_H
#define GLSL_TESSELLATION_CONTROL_SHADER_H
#include "glsl_shader.h"

struct glsl_tessellation_control_shader_input {};
									  
struct glsl_tessellation_control_shader_output {};


class glsl_tessellation_control_shader : public glsl_shader
{
public:
	glsl_tessellation_control_shader() = default;

	glsl_tessellation_control_shader(const glsl_tessellation_control_shader&) = delete;
	glsl_tessellation_control_shader& operator=(const glsl_tessellation_control_shader&) = delete;

	~glsl_tessellation_control_shader() = default;

private:

	glsl_tessellation_control_shader_input _input;

	glsl_tessellation_control_shader_output _output;

public:

	bool generate_template(const std::string& pipeline_dir) override
	{
		return false;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::TESS_CONTROL_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("\\") + 1) + ".tesc");
		return true;
	}

};

class glsl_tessellation_control_shader_template_parameters
{};

class glsl_tessellation_control_shader_template
{
};


#endif
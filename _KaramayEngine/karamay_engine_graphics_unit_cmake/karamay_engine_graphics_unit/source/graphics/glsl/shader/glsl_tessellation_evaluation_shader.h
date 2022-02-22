#ifndef GLSL_TESSELLATION_EVALUATION_SHADER_H
#define GLSL_TESSELLATION_EVALUATION_SHADER_H
#include "glsl_shader.h"

struct glsl_tessellation_evaluation_shader_input {};

struct glsl_tessellation_evaluation_shader_output {};

class glsl_tessellation_evaluation_shader : public glsl_shader
{
public:
	glsl_tessellation_evaluation_shader() = default;

	glsl_tessellation_evaluation_shader(const glsl_tessellation_evaluation_shader&) = delete;
	glsl_tessellation_evaluation_shader& operator=(const glsl_tessellation_evaluation_shader&) = delete;

	~glsl_tessellation_evaluation_shader() = default;

private:

	glsl_tessellation_evaluation_shader_input _input;
	glsl_tessellation_evaluation_shader_output _output;

public:

	bool generate_template(const std::string& pipeline_dir) override
	{
		return false;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::TESS_EVALUATION_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("\\") + 1) + ".tese");
		return false;
	}

};

#endif
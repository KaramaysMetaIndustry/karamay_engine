#ifndef GLSL_FRAGMENT_SHADER_H
#define GLSL_FRAGMENT_SHADER_H
#include "glsl_shader.h"

struct glsl_fragment_shader_input {};

struct glsl_fragment_shader_output {};

class glsl_fragment_shader : public glsl_shader
{
public:
	glsl_fragment_shader() = default;

	glsl_fragment_shader(const glsl_fragment_shader&) = delete;
	glsl_fragment_shader operator=(const glsl_fragment_shader&) = delete;

	~glsl_fragment_shader() = default;

private:

	glsl_fragment_shader_input _input;

	glsl_fragment_shader_output _output;

public:

	bool generate_template(const std::string& pipeline_dir) override
	{
		std::ifstream _file;
		std::string _content = "#version 460\n";
		return false;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::FRAGMENT_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("\\") + 1) + ".frag");
		return _shader->get_compile_status();
	}

};


#endif
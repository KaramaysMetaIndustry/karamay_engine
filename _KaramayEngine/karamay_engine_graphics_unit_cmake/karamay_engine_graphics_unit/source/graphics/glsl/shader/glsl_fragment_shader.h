#ifndef GLSL_FRAGMENT_SHADER_H
#define GLSL_FRAGMENT_SHADER_H
#include "glsl_shader.h"

struct glsl_fragment_shader_input_item
{
	std::string type_name;
	std::string var_name;
};
struct glsl_fragment_shader_output_item {};

// .frag
class glsl_fragment_shader : public glsl_shader
{
public:
	glsl_fragment_shader() = default;

	glsl_fragment_shader(const glsl_fragment_shader&) = delete;
	glsl_fragment_shader operator=(const glsl_fragment_shader&) = delete;

	~glsl_fragment_shader() = default;

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

private:
	std::vector<glsl_fragment_shader_input_item> _input_items;
	std::vector<glsl_fragment_shader_output_item> _output_items;

protected:

	void _add_input_item(glsl_fragment_shader_input_item input_item)
	{}

	void _add_output_item(glsl_fragment_shader_output_item output_item)
	{}

};

class glsl_fragment_shader_template_parameters
{

};

class glsl_fragment_shader_template final : glsl_fragment_shader
{
	glsl_fragment_shader* generate_instance() noexcept { return nullptr; }
};


#endif
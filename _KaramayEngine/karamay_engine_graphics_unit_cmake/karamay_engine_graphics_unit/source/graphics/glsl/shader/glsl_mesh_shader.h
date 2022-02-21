#ifndef GLSL_MESH_SHADER_H
#define GLSL_MESH_SHADER_H
#include "glsl_shader.h"

// .mesh
class glsl_mesh_shader : public glsl_shader
{
public:
	glsl_mesh_shader() = default;

	glsl_mesh_shader(const glsl_mesh_shader&) = delete;
	glsl_mesh_shader& operator=(const glsl_mesh_shader&) = delete;

	~glsl_mesh_shader() = default;

public:

	bool generate_template(const std::string& pipeline_dir) override
	{
		std::ifstream _file;
		std::string _content = "#version 460\n";
		return false;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::MESH_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("/") + 1) + ".mesh");
		return _shader->get_compile_status();
	}
};

class glsl_mesh_shader_template_parameters
{

};

class glsl_mesh_shader_template final : glsl_mesh_shader
{

};


#endif
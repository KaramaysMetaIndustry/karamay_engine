#ifndef GLSL_GEOMETRY_SHADER_H
#define GLSL_GEOMETRY_SHADER_H
#include "glsl_shader.h"

class glsl_geometry_shader : public glsl_shader
{
public:
	glsl_geometry_shader() = default;

	glsl_geometry_shader(const glsl_geometry_shader&) = delete;
	glsl_geometry_shader operator=(const glsl_geometry_shader&) = delete;

	~glsl_geometry_shader() = default;

public:

	bool generate_template(const std::string& pipeline_dir) override
	{
		return false;
	}

	bool load(const std::string& pipeline_dir) override
	{
		_shader = new gl_shader(gl_shader_type::GEOMETRY_SHADER, pipeline_dir + "/" + pipeline_dir.substr(pipeline_dir.find_last_of("\\") + 1) + ".geom");
		return _shader->get_compile_status();
	}

};

class glsl_geometry_shader_template_parameters final
{
};

class glsl_geometry_shader_template final : public glsl_geometry_shader
{
	glsl_geometry_shader* generate_instance(glsl_geometry_shader_template_parameters* parameters) noexcept { return nullptr; }
};


#endif
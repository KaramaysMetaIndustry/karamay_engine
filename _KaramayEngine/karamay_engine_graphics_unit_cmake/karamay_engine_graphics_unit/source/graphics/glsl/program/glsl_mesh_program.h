#ifndef GLSL_MESH_PROGRAM_H
#define GLSL_MESH_PROGRAM_H
#include "glsl_program.h"
#include "graphics/glsl/shader/glsl_task_shader.h"
#include "graphics/glsl/shader/glsl_mesh_shader.h"

class glsl_mesh_pipeline_program : public glsl_program
{
public:
	glsl_mesh_pipeline_program() = default;

	glsl_mesh_pipeline_program(const glsl_mesh_pipeline_program&) = delete;
	glsl_mesh_pipeline_program& operator=(const glsl_mesh_pipeline_program&) = delete;

	~glsl_mesh_pipeline_program() = default;

public:

	bool load(const std::string& pipeline_dir) override
	{
		std::vector<gl_shader*> _real_shaders;
		for (auto _shader : _shaders)
		{
			_shader->load(pipeline_dir);
			_real_shaders.push_back(_shader->get_shader());
		}

		_program = new gl_program();
		if (_program->load(_real_shaders))
			return true;
		else
			return false;
	}

	bool generate_template(const std::string& pipeline_dir) override
	{
		return false;
	}
};

class glsl_mesh_pipeline_template_parameters
{};

class glsl_mesh_pipeline_template
{
private:

	glsl_task_shader_template* _task_template;
	glsl_mesh_shader_template* _mesh_template;

public:


};

#endif
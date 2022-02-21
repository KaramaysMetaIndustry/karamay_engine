#ifndef GLSL_COMPUTE_PROGRAM_H
#define GLSL_COMPUTE_PROGRAM_H
#include "glsl_program.h"
#include "graphics/glsl/shader/glsl_compute_shader.h"

class glsl_compute_pipeline_program : public glsl_program
{
public:
	glsl_compute_pipeline_program() = default;

	glsl_compute_pipeline_program(const glsl_compute_pipeline_program&) = delete;
	glsl_compute_pipeline_program& operator=(const glsl_compute_pipeline_program&) = delete;

	~glsl_compute_pipeline_program() = default;

public:

	bool load(const std::string& pipeline_dir) override
	{
		if (_shaders.size() != 1) return false;

		std::vector<gl_shader*> _real_shaders;
		for (auto _shader : _shaders)
		{
			_shader->load(pipeline_dir);
			_real_shaders.push_back(_shader->get_shader());
		}

		_program = new gl_program();
		if (_program->load(_real_shaders))
		{
			return true;
		}
		else
		{
			return false;
		}

		return true;
	}

	bool generate_template(const std::string& pipeline_dir) override
	{
		return false;
	}

};

class glsl_compute_pipeline_template_parameters
{
private:

	glsl_compute_shader_template_parameters* _comp_shader_template_parameters;

};

class glsl_compute_pipeline_template
{
private:

	glsl_compute_shader_template* _comp_template;

public:

	glsl_compute_pipeline_program* generate(glsl_compute_pipeline_template_parameters* parameters) noexcept
	{
		return nullptr;
	}

};


#define def_computePipelineProgram(name)\
class glsl_##name##_pipeline_program : public glsl_compute_pipeline_program\
{\
public:\

#define decl_computePipelineProgram(name)\
class glsl_##name##_pipeline_program* _##name##_pipeline_program = new glsl_##name##_pipeline_program();



#endif
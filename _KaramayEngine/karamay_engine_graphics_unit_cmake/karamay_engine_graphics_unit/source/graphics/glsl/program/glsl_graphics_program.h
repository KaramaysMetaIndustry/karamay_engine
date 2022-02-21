#ifndef GLSL_GRAPHICS_PROGRAM_H
#define GLSL_GRAPHICS_PROGRAM_H
#include "glsl_program.h"
#include "graphics/glsl/shader/glsl_vertex_shader.h"
#include "graphics/glsl/shader/glsl_tessellation_control_shader.h"
#include "graphics/glsl/shader/glsl_tessellation_evaluation_shader.h"
#include "graphics/glsl/shader/glsl_geometry_shader.h"
#include "graphics/glsl/shader/glsl_fragment_shader.h"

class glsl_graphics_pipeline_program : public glsl_program
{
public:
	glsl_graphics_pipeline_program() = default;
	glsl_graphics_pipeline_program(const glsl_graphics_pipeline_program&) = delete;
	glsl_graphics_pipeline_program& operator=(const glsl_graphics_pipeline_program&) = delete;

	~glsl_graphics_pipeline_program() = default;

protected:

	std::string _path;

public:

	bool load(const std::string& pipeline_dir) override
	{
		// generate template, if has no file, generate
		// generate template, if has file and but 'force' is active generate file

		// if has file and forces is not active, load file and validate with template
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

class glsl_graphic_pipeline_template_parameters
{
private:

	glsl_vertex_shader_template_parameters* _vert_template_parameters;
	glsl_tessellation_control_shader_template_parameters* _tesc_template_parameters;
	glsl_tessellation_evaluation_shader_template_parameters* _tese_template_parameters;
	glsl_geometry_shader_template_parameters* _gs_template_parameters;
	glsl_fragment_shader_template_parameters* _frag_template_parameters;

};

class glsl_graphics_pipeline_template
{
private:

	glsl_vertex_shader_template* _vert_template;
	glsl_tessellation_control_shader_template* _tesc_template;
	glsl_tessellation_evaluation_shader_template* _tese_template;
	glsl_geometry_shader_template* _gs_template;
	glsl_fragment_shader_template* _frag_template;

public:

	glsl_graphics_pipeline_program* generate(glsl_graphic_pipeline_template_parameters* parameters) noexcept
	{
		return nullptr;
	}




};


#define def_graphicsPipelineProgram(name)\
class glsl_##name##_pipeline_program : public glsl_graphics_pipeline_program\
{\
public:\

#define decl_graphicsPipelineProgram(name)\
glsl_##name##_pipeline_program* _##name##_pipeline_program = new glsl_##name##_pipeline_program();




#endif
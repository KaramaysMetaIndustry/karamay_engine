#ifndef GLSL_GRAPHICS_PROGRAM_H
#define GLSL_GRAPHICS_PROGRAM_H
#include "glsl_pipeline_program.h"
#include "graphics/glsl/shader/glsl_vertex_shader.h"
#include "graphics/glsl/shader/glsl_tessellation_control_shader.h"
#include "graphics/glsl/shader/glsl_tessellation_evaluation_shader.h"
#include "graphics/glsl/shader/glsl_geometry_shader.h"
#include "graphics/glsl/shader/glsl_fragment_shader.h"

class glsl_graphics_pipeline_program : public glsl_pipeline_program
{
public:
	glsl_graphics_pipeline_program() = default;

	glsl_graphics_pipeline_program(const glsl_graphics_pipeline_program&) = delete;
	glsl_graphics_pipeline_program& operator=(const glsl_graphics_pipeline_program&) = delete;

	~glsl_graphics_pipeline_program() = default;

private:

	std::unique_ptr<glsl_vertex_shader> _vert = {};
	std::unique_ptr<glsl_tessellation_control_shader> _tesc = {};
	std::unique_ptr<glsl_tessellation_evaluation_shader> _tese = {};
	std::unique_ptr<glsl_geometry_shader> _geom = {};
	std::unique_ptr<glsl_fragment_shader> _frag = {};

public:

	bool load(const std::string& pipeline_dir) override;

	glsl_vertex_shader* invoke_vertex_shader() const noexcept { return _vert.get(); }
	glsl_tessellation_control_shader* invoke_tessellation_control_shader() const noexcept { return _tesc.get(); }
	glsl_tessellation_evaluation_shader* invoke_tessellation_evaluation_shader() const noexcept { return _tese.get(); }
	glsl_geometry_shader* invoke_geometry_shader() const noexcept { return _geom.get(); }
	glsl_fragment_shader* invoke_fragment_shader() const noexcept { return _frag.get(); }

};

class glsl_graphic_pipeline_template_parameters
{
};

class glsl_graphics_pipeline_template
{

public:

	glsl_graphics_pipeline_program* create_instance(const std::string& name) noexcept { return nullptr; }

	glsl_graphics_pipeline_program* load_instance(const std::string& path) noexcept { return nullptr; }

	glsl_graphics_pipeline_program* invoke_instance(const std::string& name) noexcept { return nullptr; }

};

#define def_graphicsPipelineProgram(name)\
class glsl_##name##_pipeline_program : public glsl_graphics_pipeline_program\
{\
public:\

#define decl_graphicsPipelineProgram(name)\
glsl_##name##_pipeline_program* _##name##_pipeline_program = new glsl_##name##_pipeline_program();




#endif
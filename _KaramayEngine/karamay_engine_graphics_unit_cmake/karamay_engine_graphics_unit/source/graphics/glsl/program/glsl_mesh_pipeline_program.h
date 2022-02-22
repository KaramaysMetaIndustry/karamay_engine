#ifndef GLSL_MESH_PROGRAM_H
#define GLSL_MESH_PROGRAM_H
#include "glsl_pipeline_program.h"
#include "graphics/glsl/shader/glsl_task_shader.h"
#include "graphics/glsl/shader/glsl_mesh_shader.h"
#include "graphics/glsl/shader/glsl_fragment_shader.h"

class glsl_mesh_pipeline_program : public glsl_pipeline_program
{
public:
	glsl_mesh_pipeline_program() = default;

	glsl_mesh_pipeline_program(const glsl_mesh_pipeline_program&) = delete;
	glsl_mesh_pipeline_program& operator=(const glsl_mesh_pipeline_program&) = delete;

	~glsl_mesh_pipeline_program() = default;

public:

	bool load(const std::string& pipeline_dir) override;

};

class glsl_mesh_pipeline_template_parameters
{};

class glsl_mesh_pipeline_template
{};

#endif
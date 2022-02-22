#ifndef GLSL_COMPUTE_PROGRAM_H
#define GLSL_COMPUTE_PROGRAM_H
#include "glsl_pipeline_program.h"
#include "graphics/glsl/shader/glsl_compute_shader.h"

class glsl_compute_pipeline_program : public glsl_pipeline_program
{
public:
	glsl_compute_pipeline_program() = default;

	glsl_compute_pipeline_program(const glsl_compute_pipeline_program&) = delete;
	glsl_compute_pipeline_program& operator=(const glsl_compute_pipeline_program&) = delete;

	~glsl_compute_pipeline_program() = default;

public:

	bool load(const std::string& pipeline_dir) override;

};

class glsl_compute_pipeline_template_parameters
{
};

class glsl_compute_pipeline_template
{
};


#define def_computePipelineProgram(name)\
class glsl_##name##_pipeline_program : public glsl_compute_pipeline_program\
{\
public:\

#define decl_computePipelineProgram(name)\
class glsl_##name##_pipeline_program* _##name##_pipeline_program = new glsl_##name##_pipeline_program();



#endif
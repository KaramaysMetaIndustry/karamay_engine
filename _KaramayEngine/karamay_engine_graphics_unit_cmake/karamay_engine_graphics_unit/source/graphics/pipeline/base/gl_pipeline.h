#include "graphics/program/gl_program.h"

class gl_pipeline_parameters
{

};

class gl_pipeline 
{

protected:
	
	gl_pipeline() = default;

	std::shared_ptr<gl_program> _program;

};
#ifndef GL_PIPELINE_H
#define GL_PIPELINE_H

#include "glsl/glsl.h"

class gl_pipeline
{
public:

	virtual bool load(const std::string& pipeline_dir) noexcept = 0;

	/*virtual bool install(gl_program* program) noexcept = 0;*/
	
	virtual void enable() noexcept = 0;
	
	virtual void disable() noexcept = 0;

};

#endif
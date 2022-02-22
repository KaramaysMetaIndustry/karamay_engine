#ifndef GL_PIPELINE_H
#define GL_PIPELINE_H
#include "graphics/glsl/glsl.h"
#include "graphics/resource/program/gl_program.h"

class gl_pipeline
{
protected:

	std::unique_ptr<gl_program> _program = {};

public:

	virtual bool load(const std::string& pipeline_dir) noexcept { return false; };
	
	virtual void enable() noexcept;
	
	virtual void disable() noexcept;

};

#endif
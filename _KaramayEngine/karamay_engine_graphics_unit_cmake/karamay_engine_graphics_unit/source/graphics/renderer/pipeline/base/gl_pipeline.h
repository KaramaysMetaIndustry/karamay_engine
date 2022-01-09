#ifndef GL_PIPELINE_H
#define GL_PIPELINE_H

#include "glsl/glsl.h"
#include "resource/program/gl_program.h"

class gl_pipeline
{
public:
	virtual bool load(const std::string& pipeline_dir) noexcept = 0;
	virtual void enable() noexcept = 0;
	virtual void disable() noexcept = 0;

};

#endif
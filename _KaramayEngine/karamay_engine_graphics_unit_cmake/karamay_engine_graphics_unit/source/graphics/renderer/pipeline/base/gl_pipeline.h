#ifndef GL_PIPELINE_H
#define GL_PIPELINE_H

#include "glsl/glsl.h"
#include "resource/program/gl_program.h"

class gl_pipeline
{
public:
	virtual bool load(const std::string& pipeline_dir) = 0;
};

#endif
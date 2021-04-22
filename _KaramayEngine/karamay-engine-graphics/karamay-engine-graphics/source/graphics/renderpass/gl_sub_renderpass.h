#pragma once
#include "public/stl.h"
#include "graphics/pipeline/gl_program_pipeline.h"
#include "graphics/framebuffer/user/gl_framebuffer.h"

class gl_sub_renderpass
{
public:



private:
	std::shared_ptr<gl_program_pipeline> program_pipeline;

	std::shared_ptr<gl_framebuffer> framebuffer;

public:
	gl_sub_renderpass();

	virtual ~gl_sub_renderpass();

};


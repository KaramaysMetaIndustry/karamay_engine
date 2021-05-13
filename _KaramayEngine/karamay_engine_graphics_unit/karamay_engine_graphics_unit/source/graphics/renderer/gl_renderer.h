#pragma once
#include "graphics/pipeline/gl_pipeline_base.h"
#include "graphics/framebuffer/gl_framebuffer.h"
#include "graphics/framebuffer/gl_default_framebuffer.h"


class gl_renderer
{
protected:

	std::shared_ptr<gl_default_framebuffer> _final_framebuffer;
	
	std::unordered_map<std::string, std::shared_ptr<gl_framebuffer>> _framebuffers_map;

	std::unordered_map<std::string, std::shared_ptr<gl_pipeline_base>> _pipelines_map;

public:
	virtual void construct() {}

	virtual void initialize() {}

	virtual void render(std::float_t delta_time)
	{

	}

};


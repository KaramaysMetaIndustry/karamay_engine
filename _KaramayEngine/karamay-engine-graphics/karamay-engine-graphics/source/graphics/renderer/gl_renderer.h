#pragma once
#include "graphics/program/gl_program.h"
#include "graphics/framebuffer/gl_framebuffer.h"
#include "graphics/framebuffer/gl_default_framebuffer.h"


class gl_renderer
{
protected:
	std::shared_ptr<gl_default_framebuffer> _final_framebuffer;
	
	std::unordered_map<std::string, std::shared_ptr<gl_framebuffer>> _framebuffers_map;

	std::unordered_map<std::string, std::shared_ptr<gl_program>> _programs_map;

public:
	virtual void construct() {}

	virtual void initialize() {}

	virtual void render(std::float_t delta_time) {}

};


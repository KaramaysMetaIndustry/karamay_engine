#pragma once
#include "graphics/pipeline/gl_pipeline_base.h"
#include "graphics/texture/texture_2d/gl_texture_2d.h"
#include "graphics/texture/texture_2d/gl_texture_2d_multisample.h"
#include "graphics/renderbuffer/gl_renderbuffer.h"
#include "graphics/renderbuffer/gl_multisample_renderbuffer.h"

struct gl_renderer_pass
{
	
};


class gl_renderer
{

	gl_renderer(const std::string& config_path) {}

	gl_renderer(const std::vector<gl_renderer_pass>& passes) {}

public:

	auto& add_pass(const std::shared_ptr<gl_pipeline_base>& pipeline)
	{

		return *this;
	}

private:

	std::vector<std::shared_ptr<gl_pipeline_base>> _pipelines;

};


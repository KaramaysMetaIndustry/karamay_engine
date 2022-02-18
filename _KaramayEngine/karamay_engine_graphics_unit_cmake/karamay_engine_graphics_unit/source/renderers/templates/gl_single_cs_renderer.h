#ifndef GL_SINGLE_CS_RENDERER_H
#define GL_SINGLE_CS_RENDERER_H

#include "graphics/renderer/gl_renderer.h"

DEFINE_RENDERER_BEGIN(gl_single_cs_renderer)

	def_computePipelineProgram(pp)
		def_computeShader()
		}; decl_computeShader();
	}; decl_computePipelineProgram(pp);

	IMPLEMENTATION_FUNC_BUILD()
	{
		_pp = builder.build_compute_pipeline(_pp_pipeline_program);
		if (!_pp->load("shaders\\renderers\\single_cs_renderer\\pp"))
		{
			return false;
		}
		return true;
	}

	IMPLEMENTATION_FUNC_RENDER()
	{
		_pp->enable();
		_pp->dispatch(512, 2, 1);
		_pp->disable();
	}

	private:
		gl_compute_pipeline* _pp;

DEFINE_RENDERER_END

#endif
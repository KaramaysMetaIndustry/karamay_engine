#ifndef GL_SHADER_TOY_RENDERER_H
#define GL_SHADER_TOY_RENDERER_H

#include "graphics/renderer/gl_renderer.h"

DEFINE_RENDERER_BEGIN(gl_shader_toy_renderer)

	def_graphicsPipelineProgram(pp)
	def_vertexShader()
			}; decl_vertexShader();
	def_fragmentShader()
			}; decl_fragmentShader();
	}; decl_graphicsPipelineProgram(pp);

	IMPLEMENTATION_FUNC_BUILD()
	{
		_pp = builder.build_graphics_pipeline(_pp_pipeline_program);
		if (!_pp->load("shaders\\renderers\\shader_toy_renderer\\pp")) return false;

		{
			_pp->rasterizer.enable_multisample = true;
			_pp->rasterizer.enable_sample_shading = true;
			_pp->rasterizer.sample_shading_rate = 1.1f;
			_pp->rasterizer.enable_line_smooth = true;
			_pp->rasterizer.enable_polygon_smooth = true;
			_pp->rasterizer.enable_polygon_offset_fill = true;
			_pp->rasterizer.cull_face.enable = false; // disable cull face

			_pp->fragment_preprocessor.scissor_test.enable = false;
			_pp->fragment_preprocessor.scissor_test.rectangle.x = 100;
			_pp->fragment_preprocessor.scissor_test.rectangle.y = 100;
			_pp->fragment_preprocessor.scissor_test.rectangle.width = 900;
			_pp->fragment_preprocessor.scissor_test.rectangle.height = 900;

			_pp->fragment_preprocessor.multisample_fragment_operations.enable_sample_coverage = true;
			_pp->fragment_preprocessor.multisample_fragment_operations.inverted = true;
			_pp->fragment_preprocessor.multisample_fragment_operations.sample_coverage_value = 1.2f;
			_pp->fragment_preprocessor.multisample_fragment_operations.enable_sample_mask = true;

			_pp->fragment_postprocessor.stencil_test.enable = false;
			_pp->fragment_postprocessor.stencil_test.front_face_func = gl_stencil_func::LEQUAL;
			_pp->fragment_postprocessor.stencil_test.back_face_func = gl_stencil_func::NEVER;
			_pp->fragment_postprocessor.depth_test.enable = false;
			_pp->fragment_postprocessor.depth_test.func = gl_depth_func::GREATER;
			_pp->fragment_postprocessor.enable_framebuffer_srgb = false; // if true -> more lighter
			_pp->fragment_postprocessor.enable_dither = true;
		}

		_pp->render_target().set_default();
		return true;
	}

	IMPLEMENTATION_FUNC_RENDER()
	{
		default_framebuffer->switch_draw_buffer(gl_default_framebuffer_draw_buffer::LEFT);
#ifdef _DEBUG
		if (!_pp) throw std::exception("mesh pipeline must not be null");
#endif
		_pp->enable();
		_acc_time += delta_time * 2;
		glUniform1f(glGetUniformLocation(_pp->program().get_program_handle(), "iTime"), _acc_time);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		_pp->disable();
	}

private:
	gl_graphics_pipeline* _pp;

	float _acc_time = 0.0f;

DEFINE_RENDERER_END


#endif
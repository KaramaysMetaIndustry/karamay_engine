#ifndef GL_SINGLE_FS_RENDERER_H
#define GL_SINGLE_FS_RENDERER_H

#include "graphics/renderer/gl_renderer.h"

DEFINE_RENDERER_BEGIN(gl_single_fs_renderer)


	def_graphicsPipelineProgram(pp)
		def_vertexShader()
		}; decl_vertexShader();
		def_fragmentShader()
		}; decl_fragmentShader();
	}; decl_graphicsPipelineProgram(pp);

	IMPLEMENTATION_FUNC_BUILD()
	{
		_pp = builder.build_graphics_pipeline(_pp_pipeline_program);
		if (!_pp->load("shaders\\renderers\\single_fs_renderer\\pp")) return false;
	
		{
			_pp->vertex_postprocessor.provoke_mode;
			_pp->vertex_postprocessor.viewport.index = 1;
			_pp->vertex_postprocessor.viewport.x = 0;
			_pp->vertex_postprocessor.viewport.y = 0;
			_pp->vertex_postprocessor.viewport.width = 0;
			_pp->vertex_postprocessor.viewport.height = 0;
			_pp->vertex_postprocessor.origin;
			_pp->vertex_postprocessor.depth_mode;

			_pp->rasterizer.enable_multisample = true;
			_pp->rasterizer.enable_sample_shading = true;
			_pp->rasterizer.sample_shading_rate = 1.1f;
			_pp->rasterizer.enable_line_smooth = true;
			_pp->rasterizer.enable_polygon_smooth = true;
			_pp->rasterizer.enable_polygon_offset_fill = true;

			// ²Ã¼ô²âÊÔ
			_pp->fragment_preprocessor.scissor_test.enable = true;
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
			_pp->fragment_postprocessor.enable_framebuffer_srgb = true;
			_pp->fragment_postprocessor.enable_dither = true;
		}

		_pp->render_target().set_default();
	}

	IMPLEMENTATION_FUNC_RENDER()
	{
		//default_framebuffer->set_color_cache(0.0f + delta_time, 1.0f, 0.0f, 1.0f);
		default_framebuffer->switch_draw_buffer(gl_default_framebuffer_draw_buffer::LEFT);
		default_framebuffer->clear_color_buffer();
#ifdef _DEBUG
		if (!_pp) throw std::exception("mesh pipeline must not be null");
#endif
		_pp->enable();
		_acc_time += delta_time * 2;
		glUniform1f(glGetUniformLocation(_pp->program().get_program_handle(), "iTime"), _acc_time);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		/*auto _fence = std::make_shared<gl_fence>();
		_fence->client_wait(1);*/
		_pp->disable();
	}

private:
	gl_graphics_pipeline* _pp;

	float _acc_time = 0.0f;

DEFINE_RENDERER_END

#endif
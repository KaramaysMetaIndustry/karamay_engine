#ifndef GL_SINGLE_GP_RENDERER_H
#define GL_SINGLE_GP_RENDERER_H

#include "graphics/renderer/gl_renderer.h"

DEFINE_RENDERER_BEGIN(gl_single_gp_renderer)
	def_graphicsPipelineProgram(pp)
		def_vertexShader()
		}; decl_vertexShader();
		def_fragmentShader()
		}; decl_fragmentShader();
	}; decl_graphicsPipelineProgram(pp);


	IMPLEMENTATION_FUNC_BUILD()
	{
		//float vertices[] = {
		//	// 第一个三角形
		//	0.5f, 0.5f, 0.0f,   // 右上角
		//	0.5f, -0.5f, 0.0f,  // 右下角
		//	-0.5f, 0.5f, 0.0f,  // 左上角
		//	// 第二个三角形
		//	0.5f, -0.5f, 0.0f,  // 右下角
		//	-0.5f, -0.5f, 0.0f, // 左下角
		//	-0.5f, 0.5f, 0.0f   // 左上角
		//};

		float vertices[] = {
			0.5f, 0.5f, 0.0f,   // 右上角
			0.5f, -0.5f, 0.0f,  // 右下角
			-0.5f, -0.5f, 0.0f, // 左下角
			-0.5f, 0.5f, 0.0f   // 左上角
		};

		unsigned int indices[] = { // 注意索引从0开始! 
			0, 1, 3, // 第一个三角形
			1, 2, 3  // 第二个三角形
		};


		_pp = builder.build_graphics_pipeline(_pp_pipeline_program);
		if (!_pp->load("shaders\\renderers\\single_gp_renderer\\pp"))
		{
			return false;
		}

		auto& _vl = _pp->vertex_launcher();

		{
			_pp->vertex_postprocessor.provoke_mode;
			_pp->vertex_postprocessor.origin;
			_pp->vertex_postprocessor.depth_mode;

			_pp->rasterizer.enable_multisample = true;
			_pp->rasterizer.enable_sample_shading = true;
			_pp->rasterizer.sample_shading_rate = 1.1f;
			_pp->rasterizer.enable_line_smooth = true;
			_pp->rasterizer.enable_polygon_smooth = true;
			_pp->rasterizer.enable_polygon_offset_fill = true;
			_pp->rasterizer.cull_face.enable = false; // diable cull face

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
		default_framebuffer->set_color_cache(1.0f, 0.0f, 0.0f, 1.0f);
		default_framebuffer->switch_draw_buffer(gl_default_framebuffer_draw_buffer::LEFT);
		default_framebuffer->clear_color_buffer();
		_pp->enable();
		_pp->unsyncable_draw_arrays(0, 4);
		_pp->disable();
	}

private:

	gl_graphics_pipeline* _pp;

DEFINE_RENDERER_END

#endif
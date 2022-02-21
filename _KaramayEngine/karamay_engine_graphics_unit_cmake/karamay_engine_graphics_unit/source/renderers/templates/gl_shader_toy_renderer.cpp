#include "gl_shader_toy_renderer.h"
#include "graphics/glsl/program/glsl_graphics_pipeline_program.h"
#include "engine/karamay_engine.h"

namespace gl_shader_toy_renderer_resource
{
	def_graphicsPipelineProgram(vp)

		def_vertexShader()
		}; decl_vertexShader();

		def_fragmentShader()
		}; decl_fragmentShader();

	};
}

gl_shader_toy_renderer* gl_shader_toy_renderer::_instance = nullptr;

bool gl_shader_toy_renderer::attach() noexcept
{
	if (!_shader_toy_gpp)
	{
		auto _vp = new gl_shader_toy_renderer_resource::glsl_vp_pipeline_program();
		_vp->load(karamay_engine::get_engine_root() + "shaders\\renderers\\shader_toy_renderer\\pp");
		_shader_toy_gpp = std::make_unique<gl_graphics_pipeline>();
		if (!_shader_toy_gpp || !_shader_toy_gpp->load(_vp))
		{
			return false;
		}
		
		{
			_shader_toy_gpp->rasterizer.enable_multisample = true;
			_shader_toy_gpp->rasterizer.enable_sample_shading = true;
			_shader_toy_gpp->rasterizer.sample_shading_rate = 1.1f;
			_shader_toy_gpp->rasterizer.enable_line_smooth = true;
			_shader_toy_gpp->rasterizer.enable_polygon_smooth = true;
			_shader_toy_gpp->rasterizer.enable_polygon_offset_fill = true;
			_shader_toy_gpp->rasterizer.cull_face.enable = false; // disable cull face

			_shader_toy_gpp->fragment_preprocessor.scissor_test.enable = false;
			_shader_toy_gpp->fragment_preprocessor.scissor_test.rectangle.x = 100;
			_shader_toy_gpp->fragment_preprocessor.scissor_test.rectangle.y = 100;
			_shader_toy_gpp->fragment_preprocessor.scissor_test.rectangle.width = 900;
			_shader_toy_gpp->fragment_preprocessor.scissor_test.rectangle.height = 900;

			_shader_toy_gpp->fragment_preprocessor.multisample_fragment_operations.enable_sample_coverage = true;
			_shader_toy_gpp->fragment_preprocessor.multisample_fragment_operations.inverted = true;
			_shader_toy_gpp->fragment_preprocessor.multisample_fragment_operations.sample_coverage_value = 1.2f;
			_shader_toy_gpp->fragment_preprocessor.multisample_fragment_operations.enable_sample_mask = true;

			_shader_toy_gpp->fragment_postprocessor.stencil_test.enable = false;
			_shader_toy_gpp->fragment_postprocessor.stencil_test.front_face_func = gl_stencil_func::LEQUAL;
			_shader_toy_gpp->fragment_postprocessor.stencil_test.back_face_func = gl_stencil_func::NEVER;
			_shader_toy_gpp->fragment_postprocessor.depth_test.enable = false;
			_shader_toy_gpp->fragment_postprocessor.depth_test.func = gl_depth_func::GREATER;
			_shader_toy_gpp->fragment_postprocessor.enable_framebuffer_srgb = false; // if true -> more lighter
			_shader_toy_gpp->fragment_postprocessor.enable_dither = true;
		}

		_shader_toy_gpp->render_target().set_default();
		return true;
	}
	return false;
}

void gl_shader_toy_renderer::render(float delta_time) noexcept
{
	if (_shader_toy_gpp)
	{
		default_framebuffer->switch_draw_buffer(gl_default_framebuffer_draw_buffer::LEFT);
#ifdef _DEBUG
		if (!_shader_toy_gpp) throw std::exception("mesh pipeline must not be null");
#endif
		_acc_time += delta_time * 2;

		_shader_toy_gpp->enable();
		glUniform1f(glGetUniformLocation(_shader_toy_gpp->program().get_program_handle(), "iTime"), _acc_time);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		_shader_toy_gpp->disable();
	}
}

bool gl_shader_toy_renderer::detach() noexcept
{
	if(_shader_toy_gpp)
	{
		_shader_toy_gpp.release();
		return true;
	}
	return false;
}

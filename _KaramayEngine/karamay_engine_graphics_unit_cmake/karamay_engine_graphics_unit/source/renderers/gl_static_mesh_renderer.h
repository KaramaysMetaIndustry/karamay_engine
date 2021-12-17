#ifndef GL_TEST_RENDERER_H
#define GL_TEST_RENDERER_H

#include "graphics/renderer/gl_renderer.h"

DEFINE_RENDERER_BEGIN(gl_static_mesh_renderer)

	IMPLEMENTATION_FUNC_BUILD()
    {
		auto _albedo_tex = builder.create_texture_2d("albedo_tex", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_albedo_tex->auto_generate_mipmaps();
		auto _normal_tex = builder.create_texture_2d("normal_tex", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_normal_tex->auto_generate_mipmaps();
		auto _metalness_tex = builder.create_texture_2d("metalness_tex", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_metalness_tex->auto_generate_mipmaps();
		auto _roughness_tex = builder.create_texture_2d("roughness_tex", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_roughness_tex->auto_generate_mipmaps();
		auto _displacement_tex = builder.create_texture_2d("displacement_tex", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_displacement_tex->auto_generate_mipmaps();
		auto _ambient_occlusion_tex = builder.create_texture_2d("ambient_occlusion_tex", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_ambient_occlusion_tex->auto_generate_mipmaps();

		glsl_vertex_shader* _vs = new glsl_vertex_shader({});
		glsl_tessellation_shader* _ts = new glsl_tessellation_shader({});
		glsl_geometry_shader* _gs = new glsl_geometry_shader({});
		glsl_fragment_shader* _fs = new glsl_fragment_shader({});
		
		// initialize pipeline, set shaders
		auto _mesh_pipeline = builder.create_graphics_pipeline("mesh_pipeline", _vs, _ts, _gs, _fs);

		// set program
		/*_mesh_pipeline->program().sampler2D("mat.albedo_map")->set_texture_2d(_albedo_map);
		_mesh_pipeline->program().sampler2D("mat.normal_map")->set_texture_2d(_normal_map);
		_mesh_pipeline->program().sampler2D("mat.metalness_map")->set_texture_2d(_metalness_map);
		_mesh_pipeline->program().sampler2D("mat.roughness_map")->set_texture_2d(_roughness_map);
		_mesh_pipeline->program().sampler2D("mat.displacement_map")->set_texture_2d(_displacement_map);
		_mesh_pipeline->program().sampler2D("mat.ambient_occlusion_map")->set_texture_2d(_ambient_occlusion_map);*/

		// set rasterizer
		_mesh_pipeline->rasterizer.discard = false;
		_mesh_pipeline->rasterizer.enable_cull_face = true;
		_mesh_pipeline->rasterizer.cull_face = gl_cull_face::BACK;
		_mesh_pipeline->rasterizer.enable_multisample = true;
		_mesh_pipeline->rasterizer.enable_sample_shading = true;
		_mesh_pipeline->rasterizer.sample_shading_rate = 1.1f;
		_mesh_pipeline->rasterizer.enable_line_smooth = true;
		_mesh_pipeline->rasterizer.enable_polygon_smooth = true;
		_mesh_pipeline->rasterizer.enable_polygon_offset_fill = true;

		// set fragment operations
		// scissor test
		_mesh_pipeline->fragment_operations.scissor_test.enable = true;
		_mesh_pipeline->fragment_operations.scissor_test.x = 0;
		_mesh_pipeline->fragment_operations.scissor_test.y = 0;
		_mesh_pipeline->fragment_operations.scissor_test.width = 1024;
		_mesh_pipeline->fragment_operations.scissor_test.height = 1024;
		// multisample fragment operations
		_mesh_pipeline->fragment_operations.multisample_fragment_operations.enable_sample_coverage = true;
		_mesh_pipeline->fragment_operations.multisample_fragment_operations.inverted = true;
		_mesh_pipeline->fragment_operations.multisample_fragment_operations.sample_coverage_value = 1.2f;
		_mesh_pipeline->fragment_operations.multisample_fragment_operations.enable_sample_mask = true;
		// stencil test
		_mesh_pipeline->fragment_operations.stencil_test.enable = false;
		_mesh_pipeline->fragment_operations.stencil_test.ref = 0;
		_mesh_pipeline->fragment_operations.stencil_test.mask = 125;
		_mesh_pipeline->fragment_operations.stencil_test.front_face_func = gl_stencil_func::LEQUAL;
		_mesh_pipeline->fragment_operations.stencil_test.back_face_func = gl_stencil_func::NEVER;
		// depth test
		_mesh_pipeline->fragment_operations.depth_test.enable = false;
		_mesh_pipeline->fragment_operations.depth_test.func = gl_depth_func::GREATER;
		// blend
		_mesh_pipeline->fragment_operations.enable_blend = true;
		// srgb 
		_mesh_pipeline->fragment_operations.enable_framebuffer_srgb = true;
		// dither
		_mesh_pipeline->fragment_operations.enable_dither = true;
		// logic operation
		_mesh_pipeline->fragment_operations.logic_operation.enable = true;
		_mesh_pipeline->fragment_operations.logic_operation.op = gl_logic_op::INVERT;

		// set vertex launcher
		auto& _vertex_launcher = _mesh_pipeline->vertex_launcher();
		_vertex_launcher.reallocate_element_slot(10);
		_vertex_launcher.reallocate_vertex_slot(16);

		// set framebuffer
		auto _tmp_fb = builder.create_framebuffer("tmp_fb", 1024, 1024);
		_tmp_fb->set_color_attachment(0, _albedo_tex, 0);
		_tmp_fb->set_color_attachment(1, _normal_tex, 0);

		// set render target
		_mesh_pipeline->render_target().set_default();

		// set callback
		ON_WINDOW_SIZE_CHANGED = [_tmp_fb](uint32 window_width, uint32 window_height)
		{
			if (!_tmp_fb) return;
			_tmp_fb->reallocate(window_width, window_height);
		};
		ON_DETACHED_FROM_DISPATCHER = []()
		{
			std::cout << "this renderer has been detached from dispatcher" << std::endl;
		};

	}

	IMPLEMENTATION_FUNC_RENDER()
	{
		// set default framebuffer
		default_framebuffer->set_color_cache(0.5f, 0.0f, 0.0f, 1.0f);
		default_framebuffer->set_stencil_cache(1);
		default_framebuffer->set_depth_cache(0.1l);
		default_framebuffer->switch_draw_buffer(gl_default_framebuffer_draw_buffer::LEFT);

		default_framebuffer->clear_color_buffer();
		default_framebuffer->clear_depth_buffer();
		default_framebuffer->clear_stencil_buffer();

		auto _mesh_pipeline = builder.graphics_pipeline("mesh_pipeline");

#ifdef _DEBUG
		if (!_mesh_pipeline) throw std::exception("mesh pipeline must not be nullptr");
#endif

		_mesh_pipeline->enable();
		auto _fence = _mesh_pipeline->draw_arrays(0, 1024);
		//_fence->client_wait(0);
		_mesh_pipeline->disable();

		_frame_count++;
	}

private:
	uint32 _frame_count = 0;

DEFINE_RENDERER_END

#endif
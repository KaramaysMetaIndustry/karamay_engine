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

		glsl_compute_shader* _cs = new glsl_compute_shader({});
		
		auto _mesh_pipeline = builder.create_graphics_pipeline("mesh_pipeline", _vs, _ts, _gs, _fs);
		auto _material_combiner_pipeline = builder.create_compute_pipeline("material_combiner_pipeline", _cs);

		// set program
		/*_mesh_pipeline->program().sampler2D("mat.albedo_map")->set_texture_2d(_albedo_map);
		_mesh_pipeline->program().sampler2D("mat.normal_map")->set_texture_2d(_normal_map);
		_mesh_pipeline->program().sampler2D("mat.metalness_map")->set_texture_2d(_metalness_map);
		_mesh_pipeline->program().sampler2D("mat.roughness_map")->set_texture_2d(_roughness_map);
		_mesh_pipeline->program().sampler2D("mat.displacement_map")->set_texture_2d(_displacement_map);
		_mesh_pipeline->program().sampler2D("mat.ambient_occlusion_map")->set_texture_2d(_ambient_occlusion_map);*/


		_mesh_pipeline->vertex_postprocessor.provoke_mode;
		_mesh_pipeline->vertex_postprocessor.viewport.index = 1;
		_mesh_pipeline->vertex_postprocessor.viewport.x = 0;
		_mesh_pipeline->vertex_postprocessor.viewport.y = 0;
		_mesh_pipeline->vertex_postprocessor.viewport.width = 0;
		_mesh_pipeline->vertex_postprocessor.viewport.height = 0;
		_mesh_pipeline->vertex_postprocessor.origin;
		_mesh_pipeline->vertex_postprocessor.depth_mode;

		_mesh_pipeline->rasterizer.enable_multisample = true;
		_mesh_pipeline->rasterizer.enable_sample_shading = true;
		_mesh_pipeline->rasterizer.sample_shading_rate = 1.1f;
		_mesh_pipeline->rasterizer.enable_line_smooth = true;
		_mesh_pipeline->rasterizer.enable_polygon_smooth = true;
		_mesh_pipeline->rasterizer.enable_polygon_offset_fill = true;
		
		_mesh_pipeline->fragment_preprocessor.scissor_test.enable = true;
		_mesh_pipeline->fragment_preprocessor.scissor_test.rectangle.x = 0;
		_mesh_pipeline->fragment_preprocessor.scissor_test.rectangle.y = 0;
		_mesh_pipeline->fragment_preprocessor.scissor_test.rectangle.width = 1024;
		_mesh_pipeline->fragment_preprocessor.scissor_test.rectangle.height = 1024;
		_mesh_pipeline->fragment_preprocessor.multisample_fragment_operations.enable_sample_coverage = true;
		_mesh_pipeline->fragment_preprocessor.multisample_fragment_operations.inverted = true;
		_mesh_pipeline->fragment_preprocessor.multisample_fragment_operations.sample_coverage_value = 1.2f;
		_mesh_pipeline->fragment_preprocessor.multisample_fragment_operations.enable_sample_mask = true;

		_mesh_pipeline->fragment_postprocessor.stencil_test.enable = false;

		_mesh_pipeline->fragment_postprocessor.stencil_test.front_face_func = gl_stencil_func::LEQUAL;
		_mesh_pipeline->fragment_postprocessor.stencil_test.back_face_func = gl_stencil_func::NEVER;
		_mesh_pipeline->fragment_postprocessor.depth_test.enable = false;
		_mesh_pipeline->fragment_postprocessor.depth_test.func = gl_depth_func::GREATER;
		_mesh_pipeline->fragment_postprocessor.enable_framebuffer_srgb = true;
		_mesh_pipeline->fragment_postprocessor.enable_dither = true;

		auto& _vertex_launcher = _mesh_pipeline->vertex_launcher();
		_vertex_launcher.reallocate_element_slot(10);
		_vertex_launcher.reallocate_vertex_slot(16);

		auto _tmp_fb = builder.create_framebuffer("tmp_fb", 1024, 1024);
		_tmp_fb->set_color_attachment(0, _albedo_tex, 0);
		_tmp_fb->set_color_attachment(1, _normal_tex, 0);

		_mesh_pipeline->render_target().set_default();

		on_window_size_changed = [_tmp_fb](uint32 window_width, uint32 window_height)
		{
			if (!_tmp_fb) return;
			_tmp_fb->reallocate(window_width, window_height);
		};

		on_renderer_attached = []()
		{
			std::cout << "this renderer has been attached to dispatcher" << std::endl;
		};

		on_renderer_detached = []()
		{
			std::cout << "this renderer has been detached from dispatcher" << std::endl;
		};
	}

	IMPLEMENTATION_FUNC_RENDER()
	{
		default_framebuffer->set_color_cache(0.5f, 0.0f, 0.0f, 1.0f);
		default_framebuffer->set_stencil_cache(1);
		default_framebuffer->set_depth_cache(0.1l);
		default_framebuffer->switch_draw_buffer(gl_default_framebuffer_draw_buffer::LEFT);
		default_framebuffer->clear_color_buffer();

		auto _mesh_pipeline = builder.graphics_pipeline("mesh_pipeline");
		auto _material_combiner_pipeline = builder.compute_pipeline("material_combiner_pipeline");

#ifdef _DEBUG
		if (!_mesh_pipeline) throw std::exception("mesh pipeline must not be null");
		if (!_material_combiner_pipeline) throw std::exception("material combiner pipeline must not be null");
#endif

		_material_combiner_pipeline->enable();
		//_material_combiner_pipeline->dispatch(1, 1, 1);
		_material_combiner_pipeline->disable();

		_mesh_pipeline->enable();
		_mesh_pipeline->unsyncable_draw_arrays(0, 1024);
		_mesh_pipeline->disable();

		_frame_count++;
	}

private:
	uint32 _frame_count = 0;

DEFINE_RENDERER_END

#endif
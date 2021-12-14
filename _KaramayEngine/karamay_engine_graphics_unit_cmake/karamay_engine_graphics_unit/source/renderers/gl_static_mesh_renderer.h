#ifndef GL_TEST_RENDERER_H
#define GL_TEST_RENDERER_H

#include "graphics/renderer/gl_renderer.h"

DEFINE_RENDERER_BEGIN(gl_static_mesh_renderer)

	IMPLEMENTATION_FUNC_BUILD()
    {
		// Builder.CreateTexture2D()
		// AutoGenerateMipmaps()
		// life time are managed by builder 
		auto _albedo_map = builder.create_texture_2d("albedo_map", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_albedo_map->build_mipmaps();
		auto _normal_map = builder.create_texture_2d("normal_map", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_normal_map->build_mipmaps();
		auto _metalness_map = builder.create_texture_2d("metalness_map", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_metalness_map->build_mipmaps();
		auto _roughness_map = builder.create_texture_2d("roughness_map", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_roughness_map->build_mipmaps();
		auto _displacement_map = builder.create_texture_2d("displacement_map", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_displacement_map->build_mipmaps();
		auto _ambient_occlusion_map = builder.create_texture_2d("ambient_occlusion_map", 1, 1024, 1024, gl_texture_internal_format::NOR_RGBA_UI8);
		_ambient_occlusion_map->build_mipmaps();

		glsl_vertex_shader* _vs = new glsl_vertex_shader({});
		glsl_tessellation_shader* _ts = new glsl_tessellation_shader({});
		glsl_geometry_shader* _gs = new glsl_geometry_shader({});
		glsl_fragment_shader* _fs = new glsl_fragment_shader({});
		auto _mesh_pipeline = builder.create_graphics_pipeline("mesh_pipeline", _vs, _ts, _gs, _fs);
		
		auto& _vertex_launcher = _mesh_pipeline->vertex_launcher();
		_vertex_launcher.reallocate_element_slot(10);
		_vertex_launcher.reallocate_vertex_slot(16);
		_vertex_launcher.execute_mapped_element_slot_handler(0, 1024, 
			[](void* data, uint32 elements_num) 
			{

			}
		);

		/*_mesh_pipeline->program().sampler2D("mat.albedo_map")->set_texture_2d(_albedo_map);
		_mesh_pipeline->program().sampler2D("mat.normal_map")->set_texture_2d(_normal_map);
		_mesh_pipeline->program().sampler2D("mat.metalness_map")->set_texture_2d(_metalness_map);
		_mesh_pipeline->program().sampler2D("mat.roughness_map")->set_texture_2d(_roughness_map);
		_mesh_pipeline->program().sampler2D("mat.displacement_map")->set_texture_2d(_displacement_map);
		_mesh_pipeline->program().sampler2D("mat.ambient_occlusion_map")->set_texture_2d(_ambient_occlusion_map);*/

		_mesh_pipeline->render_target().set_default();
		
		_mesh_pipeline->set_viewport(0, 0, 1024, 1024);
		_mesh_pipeline->set_blend_enable(true);
		_mesh_pipeline->set_blend_func(gl_blend_func_factor::ONE_MINUS_DST_COLOR, gl_blend_func_factor::CONSTANT_ALPHA);
		_mesh_pipeline->set_cull_face_enable(true);
		_mesh_pipeline->set_depth_test_enable(true);

		default_framebuffer->cache_clear_color(0.3f, 0.5f, 0.8f, 1.0f);
		default_framebuffer->cache_clear_depth(0.1l);
		default_framebuffer->cache_clear_stencil(1);
		default_framebuffer->switch_read_buffer(gl_default_framebuffer_read_buffer::LEFT);
	}

	IMPLEMENTATION_FUNC_RENDER()
	{
		// switch default framebuffer
		/*if (_frame_count % 2 != 0)
			default_framebuffer->switch_draw_buffer(gl_default_framebuffer_draw_buffer::BACK_LEFT);
		else
			default_framebuffer->switch_draw_buffer(gl_default_framebuffer_draw_buffer::BACK_LEFT);*/

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
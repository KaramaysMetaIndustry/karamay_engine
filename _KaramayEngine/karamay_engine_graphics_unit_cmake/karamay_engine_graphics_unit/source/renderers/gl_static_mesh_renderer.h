#ifndef GL_TEST_RENDERER_H
#define GL_TEST_RENDERER_H

#include "graphics/renderer/gl_renderer.h"

#define CLASS_NAME(__CLASS__)  #__CLASS__

#define BUILD_COMPUTE_PIPELINE(PP_NAME, CS)\
auto PP_NAME = builder.build_compute_pipeline(CLASS_NAME(PP_NAME), CS)\

#define BUILD_GRAPHICS_PIPELINE(PP_NAME, VS, TS, GS, FS)\
auto PP_NAME = builder.build_graphics_pipeline(CLASS_NAME(PP_NAME), VS, TS, GS, FS)

DEFINE_RENDERER_BEGIN(gl_static_mesh_renderer)

	IMPLEMENTATION_FUNC_BUILD()
    {
		auto _albedo_tex = builder.build_texture_2d(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 1);
		auto _normal_tex = builder.build_texture_2d(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 1);
		auto _metalness_tex = builder.build_texture_2d(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 1);
		auto _roughness_tex = builder.build_texture_2d(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 1);
		auto _displacement_tex = builder.build_texture_2d(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 1);
		auto _ambient_occlusion_tex = builder.build_texture_2d(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 1);
		_albedo_tex->auto_generate_mipmaps();
		_normal_tex->auto_generate_mipmaps();
		_metalness_tex->auto_generate_mipmaps();
		_roughness_tex->auto_generate_mipmaps();
		_displacement_tex->auto_generate_mipmaps();
		_ambient_occlusion_tex->auto_generate_mipmaps();

		auto _vs = new glsl_vertex_shader({});
		auto _ts = new glsl_tessellation_shader({});
		auto _gs = new glsl_geometry_shader({});
		auto _fs = new glsl_fragment_shader({});

		_mesh_pipeline = builder.build_graphics_pipeline(_vs, _ts, _gs, _fs);

		// you can reallocate or fill vertex attributes, indices, instance attributes
		// all data format are fixed after initialization, only thing you can changed only number of these attribs
		auto& _vl = _mesh_pipeline->vertex_launcher();
		_vl.reallocate_vertex_slot(16);
		_vl.reallocate_element_slot(10);

		// set pipeline fixed stage
		// you can also change these when rendering
		{
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
		}
		
		// set pipeline shader program parameters
		// explicitly specify the resource parameter uses
		// you can also change these when rendering
		{
			// set program
			_mesh_pipeline->program().sampler2D("mat.albedo_map")->set_texture_2d(_albedo_tex);
			_mesh_pipeline->program().sampler2D("mat.normal_map")->set_texture_2d(_normal_tex);
			_mesh_pipeline->program().sampler2D("mat.metalness_map")->set_texture_2d(_metalness_tex);
			_mesh_pipeline->program().sampler2D("mat.roughness_map")->set_texture_2d(_roughness_tex);
			_mesh_pipeline->program().sampler2D("mat.displacement_map")->set_texture_2d(_displacement_tex);
			_mesh_pipeline->program().sampler2D("mat.ambient_occlusion_map")->set_texture_2d(_ambient_occlusion_tex);
		}

		// set pipeline render target
		// default : global device framebuffer
		// custom framebuffer : you can operate every component of it
		// you can also change it when rendering
		_mesh_pipeline->render_target().set_default();

		default_framebuffer->set_color_cache(0.5f, 0.0f, 0.0f, 1.0f);
	}

	IMPLEMENTATION_FUNC_RENDER()
	{
		default_framebuffer->switch_draw_buffer(gl_default_framebuffer_draw_buffer::LEFT);
		default_framebuffer->clear_color_buffer();

#ifdef _DEBUG
		if (!_mesh_pipeline) throw std::exception("mesh pipeline must not be null");
#endif

		_mesh_pipeline->enable();
		_mesh_pipeline->unsyncable_draw_arrays(0, 1024);
		_mesh_pipeline->disable();
	}

private:

	gl_graphics_pipeline* _mesh_pipeline;


DEFINE_RENDERER_END

#endif
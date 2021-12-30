#ifndef GL_TEST_RENDERER_H
#define GL_TEST_RENDERER_H

#include "graphics/renderer/gl_renderer.h"
#include "graphics/renderer/pipeline/base/glsl/glsl_builder.h"

DEFINE_RENDERER_BEGIN(gl_static_mesh_renderer)

class glsl_mesh_pipeline_program : public glsl_graphics_pipeline_program
{

	uniformBlock(0, STD140, Material)
		sampler1D(Powder);
		sampler2DArrayShadow(Waiter);
		samplerBuffer(Rect);
	};
	
	shaderStorageBlock(0, STD430, ReadPosition)

	};


	vertexShader()
	
	};

	tessellationControlShader()

	};

	tessellationEvaluationShader()

	};

	geometryShader()

	};

	fragmentShader()

	};

} * _mesh_pipeline_program = new glsl_mesh_pipeline_program();
	
	
IMPLEMENTATION_FUNC_BUILD()
{
	auto _albedo_tex_2d_pool = builder.build_texture_2d_array(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 8, 1000);

	auto _albedos = builder.build_texture_view_2d_array(_albedo_tex_2d_pool, gl_texture_internal_format::NOR_RGBA_UI8, { 0, 7 }, { 0, 10 });
	auto _albedo = builder.build_texture_view_2d(_albedo_tex_2d_pool, gl_texture_internal_format::NOR_RGBA_UI8, { 0, 7 }, 11);

	auto _albedo_tex = builder.build_texture_2d(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 1);
	_albedo_tex->set_base_level(0);
	_albedo_tex->fill(0, 0, 0, 1024, 1024, gl_texture_pixel_format::RGBA, gl_texture_pixel_type::UINT8, nullptr);
	_albedo_tex->build_mipmaps();
	auto _normal_tex = builder.build_texture_2d(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 1);
	_normal_tex->build_mipmaps();
	auto _metalness_tex = builder.build_texture_2d(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 1);
	_metalness_tex->build_mipmaps();
	auto _roughness_tex = builder.build_texture_2d(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 1);
	_roughness_tex->build_mipmaps();
	auto _displacement_tex = builder.build_texture_2d(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 1);
	_displacement_tex->build_mipmaps();
	auto _ambient_occlusion_tex = builder.build_texture_2d(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 1);
	_ambient_occlusion_tex->build_mipmaps();
	auto _sky_box_tex = builder.build_texture_cube(gl_texture_internal_format::NOR_RGBA_UI8, 1024, 1024, 2);
	_sky_box_tex->fill(
		gl_cube_face_index::NEGATIVE_X, // face index
		0, // mipmap index
		0, 0, 1024, 1024, // offset + size
		gl_texture_pixel_format::RGBA, gl_texture_pixel_type::UINT8, nullptr // pixels
	);
	_sky_box_tex->build_mipmaps();

	_mesh_pipeline = builder.build_graphics_pipeline(_mesh_pipeline_program);

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
	auto _public_sampler = builder.build_sampler();
	_public_sampler->set_border_color(glm::vec4(0.5, 0.8, 0.9, 1.0f));

	// set pipeline shader program parameters
	// explicitly specify the resource parameter uses
	// you can also change these when rendering
	{
		_mesh_pipeline->program();
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

gl_graphics_pipeline* _mesh_pipeline;
gl_compute_pipeline* _mat_batch_pipeline;

DEFINE_RENDERER_END




#endif
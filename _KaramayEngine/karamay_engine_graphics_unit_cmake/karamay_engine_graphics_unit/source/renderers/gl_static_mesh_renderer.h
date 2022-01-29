#ifndef GL_TEST_RENDERER_H
#define GL_TEST_RENDERER_H

#include "graphics/renderer/gl_renderer.h"

DEFINE_RENDERER_BEGIN(gl_static_mesh_renderer)

	def_graphicsPipelineProgram(vp)

		def_uniformBlock(0, STD140, Material)
			sampler1D(Powder);
			sampler2DArrayShadow(Waiter);
			samplerBuffer(Rect);
		};
	
		def_shaderStorageBlock(0, STD430, ReadPosition)

		};

		decl_uniformBlock(Material);
		decl_shaderStorageBlock(ReadPosition);

		def_vertexShader()
			ref_uniformBlock(Material);
			ref_shaderStorageBlock(ReadPosition);
		}; decl_vertexShader();

		def_tessellationControlShader()
			ref_uniformBlock(Material);
			ref_shaderStorageBlock(ReadPosition);
		}; decl_tessellationControlShader();

		def_tessellationEvaluationShader()
			ref_uniformBlock(Material);
			ref_shaderStorageBlock(ReadPosition);
		}; decl_tessellationEvaludationShader();

		def_geometryShader()
			ref_uniformBlock(Material);
			ref_shaderStorageBlock(ReadPosition);
		}; decl_geometryShader();

		def_fragmentShader()
			ref_uniformBlock(Material);
			ref_shaderStorageBlock(ReadPosition);
		}; decl_fragmentShader();

	}; decl_graphicsPipelineProgram(vp);

	def_computePipelineProgram(mat)

		def_uniformBlock(0, STD140, Materials)
			sampler2DArray(albedoMaps);
			sampler2DArray(roughnessMaps);
		}; decl_uniformBlock(Materials);

		def_uniformBlock(1, STD140, NormalCalculatorStruct)
			sampler2DArray(slate);
			sampler1D(inputScalar);
			sampler2D(inputNormal);
			sampler3D(inputShadowScalar);
		}; decl_uniformBlock(NormalCalculatorStruct);

		def_shaderStorageBlock(0, STD430, OutMaterial)
			sampler2D(combinedAlbedoMap);
			sampler2D(combinedRoughnessMap);
		}; decl_shaderStorageBlock(OutMaterial);

		def_computeShader()
			ref_uniformBlock(Materials);
			ref_uniformBlock(NormalCalculatorStruct);
			ref_shaderStorageBlock(OutMaterial);
		}; decl_computeShader();

	} * _mat_pipeline_program = new glsl_mat_pipeline_program();
	
	class glsl_nv_mesh_pipeline_program : public glsl_mesh_pipeline_program
	{
		def_taskShader()
		}; decl_taskShader();

		def_meshShader()
		}; decl_meshShader();
	} * _nv_mesh_pipeline_program = new glsl_nv_mesh_pipeline_program();

	gl_graphics_pipeline* _vp_pipeline;
	gl_compute_pipeline* _mat_pipeline;
	gl_mesh_pipeline* _nv_mesh_pipeline;
	
	IMPLEMENTATION_FUNC_BUILD()
	{
		// build pipeline
		_vp_pipeline = builder.build_graphics_pipeline(_vp_pipeline_program);
		if (!_vp_pipeline->load("G:/PrivateRepos/Karamays/_KaramayEngine/karamay_engine_graphics_unit_cmake/karamay_engine_graphics_unit/shaders/renderers/static_mesh_renderer/mesh_pp")) return false;
		
		/*_mat_pipeline = builder.build_compute_pipeline(_mat_pipeline_program);
		if (!_mat_pipeline->load("G:/PrivateRepos/Karamays/_KaramayEngine/karamay_engine_graphics_unit_cmake/karamay_engine_graphics_unit/shaders/renderers/static_mesh_renderer/mat_pp")) return false;

		_nv_mesh_pipeline = builder.build_mesh_pipeline(_nv_mesh_pipeline_program);
		if (!_nv_mesh_pipeline->load("G:/PrivateRepos/Karamays/_KaramayEngine/karamay_engine_graphics_unit_cmake/karamay_engine_graphics_unit/shaders/renderers/static_mesh_renderer/nv_mesh_pp")) return false;*/

		// set pipeline fixed stage
		{
			_vp_pipeline->vertex_postprocessor.provoke_mode;
			_vp_pipeline->vertex_postprocessor.viewport.index = 1;
			_vp_pipeline->vertex_postprocessor.viewport.x = 0;
			_vp_pipeline->vertex_postprocessor.viewport.y = 0;
			_vp_pipeline->vertex_postprocessor.viewport.width = 0;
			_vp_pipeline->vertex_postprocessor.viewport.height = 0;
			_vp_pipeline->vertex_postprocessor.origin;
			_vp_pipeline->vertex_postprocessor.depth_mode;

			_vp_pipeline->rasterizer.enable_multisample = true;
			_vp_pipeline->rasterizer.enable_sample_shading = true;
			_vp_pipeline->rasterizer.sample_shading_rate = 1.1f;
			_vp_pipeline->rasterizer.enable_line_smooth = true;
			_vp_pipeline->rasterizer.enable_polygon_smooth = true;
			_vp_pipeline->rasterizer.enable_polygon_offset_fill = true;

			_vp_pipeline->fragment_preprocessor.scissor_test.enable = true;
			_vp_pipeline->fragment_preprocessor.scissor_test.rectangle.x = 0;
			_vp_pipeline->fragment_preprocessor.scissor_test.rectangle.y = 0;
			_vp_pipeline->fragment_preprocessor.scissor_test.rectangle.width = 1024;
			_vp_pipeline->fragment_preprocessor.scissor_test.rectangle.height = 1024;
			_vp_pipeline->fragment_preprocessor.multisample_fragment_operations.enable_sample_coverage = true;
			_vp_pipeline->fragment_preprocessor.multisample_fragment_operations.inverted = true;
			_vp_pipeline->fragment_preprocessor.multisample_fragment_operations.sample_coverage_value = 1.2f;
			_vp_pipeline->fragment_preprocessor.multisample_fragment_operations.enable_sample_mask = true;

			_vp_pipeline->fragment_postprocessor.stencil_test.enable = false;
			_vp_pipeline->fragment_postprocessor.stencil_test.front_face_func = gl_stencil_func::LEQUAL;
			_vp_pipeline->fragment_postprocessor.stencil_test.back_face_func = gl_stencil_func::NEVER;
			_vp_pipeline->fragment_postprocessor.depth_test.enable = false;
			_vp_pipeline->fragment_postprocessor.depth_test.func = gl_depth_func::GREATER;
			_vp_pipeline->fragment_postprocessor.enable_framebuffer_srgb = true;
			_vp_pipeline->fragment_postprocessor.enable_dither = true;
		}

		// set pipeline shader program parameters
		// explicitly specify the resource parameter uses
		// you can also change these when rendering
		auto& _program = _vp_pipeline->program();
		_program.uniform_block("wait");
		_program.shader_storage_block("");
		_program.atomic_uint("");

		// you can reallocate or fill vertex attributes, indices, instance attributes
		// all data format are fixed after initialization, only thing you can changed only number of these attribs
		auto& _vl = _vp_pipeline->vertex_launcher();
		_vl.reallocate_vertex_slot(16);
		_vl.reallocate_element_slot(10);
		_vl.execute_mapped_element_slot_writer(0, 1024,
			[=](void* _dst, uint64 _dst_size)
			{
			}
		);

		// set pipeline render target
		// default : global device framebuffer
		// custom framebuffer : you can operate every component of it
		// you can also change it when rendering
		auto& _rt = _vp_pipeline->render_target();
		_rt.set_default();

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

		return true;
	}

	IMPLEMENTATION_FUNC_RENDER()
	{
		default_framebuffer->set_color_cache(0.5f, 0.0f, 0.0f, 1.0f);
		default_framebuffer->switch_draw_buffer(gl_default_framebuffer_draw_buffer::LEFT);
		default_framebuffer->clear_color_buffer();
	#ifdef _DEBUG
		if (!_vp_pipeline) throw std::exception("mesh pipeline must not be null");
	#endif
		_vp_pipeline->enable();
		_vp_pipeline->unsyncable_draw_arrays(0, 1024);
		_vp_pipeline->disable();
	}

DEFINE_RENDERER_END




#endif
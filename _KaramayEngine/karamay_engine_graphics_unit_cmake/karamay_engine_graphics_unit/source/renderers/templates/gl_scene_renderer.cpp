#include "gl_scene_renderer.h"

namespace gl_scene_renderer_resource
{
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

	}; //decl_graphicsPipelineProgram(vp);

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
		}; //decl_computeShader();

	}; //*_mat_pipeline_program = new glsl_mat_pipeline_program();

	class glsl_nv_mesh_pipeline_program : public glsl_mesh_pipeline_program
	{
		def_taskShader()
	}; decl_taskShader();

		def_meshShader()
		}; decl_meshShader();
	}; //*_nv_mesh_pipeline_program = new glsl_nv_mesh_pipeline_program();
}

gl_scene_renderer* gl_scene_renderer::_instance = nullptr;

bool gl_scene_renderer::initialize() noexcept
{
	return false;
}

bool gl_scene_renderer::attach() noexcept
{
	if (!_gpp && !_cpp && !_mpp)
	{
		// build pipeline
		gl_scene_renderer_resource::glsl_vp_pipeline_program* _vp_pipeline_program = nullptr;

		_gpp.reset(builder.build_graphics_pipeline());
		if (!_gpp->load(_vp_pipeline_program)) 
			return false;

		{
			_gpp->vertex_postprocessor.provoke_mode;
			_gpp->vertex_postprocessor.viewport.index = 1;
			_gpp->vertex_postprocessor.viewport.x = 0;
			_gpp->vertex_postprocessor.viewport.y = 0;
			_gpp->vertex_postprocessor.viewport.width = 0;
			_gpp->vertex_postprocessor.viewport.height = 0;
			_gpp->vertex_postprocessor.origin;
			_gpp->vertex_postprocessor.depth_mode;

			_gpp->rasterizer.enable_multisample = true;
			_gpp->rasterizer.enable_sample_shading = true;
			_gpp->rasterizer.sample_shading_rate = 1.1f;
			_gpp->rasterizer.enable_line_smooth = true;
			_gpp->rasterizer.enable_polygon_smooth = true;
			_gpp->rasterizer.enable_polygon_offset_fill = true;

			_gpp->fragment_preprocessor.scissor_test.enable = true;
			_gpp->fragment_preprocessor.scissor_test.rectangle.x = 0;
			_gpp->fragment_preprocessor.scissor_test.rectangle.y = 0;
			_gpp->fragment_preprocessor.scissor_test.rectangle.width = 1024;
			_gpp->fragment_preprocessor.scissor_test.rectangle.height = 1024;
			_gpp->fragment_preprocessor.multisample_fragment_operations.enable_sample_coverage = true;
			_gpp->fragment_preprocessor.multisample_fragment_operations.inverted = true;
			_gpp->fragment_preprocessor.multisample_fragment_operations.sample_coverage_value = 1.2f;
			_gpp->fragment_preprocessor.multisample_fragment_operations.enable_sample_mask = true;

			_gpp->fragment_postprocessor.stencil_test.enable = false;
			_gpp->fragment_postprocessor.stencil_test.front_face_func = gl_stencil_func::LEQUAL;
			_gpp->fragment_postprocessor.stencil_test.back_face_func = gl_stencil_func::NEVER;
			_gpp->fragment_postprocessor.depth_test.enable = false;
			_gpp->fragment_postprocessor.depth_test.func = gl_depth_func::GREATER;
			_gpp->fragment_postprocessor.enable_framebuffer_srgb = true;
			_gpp->fragment_postprocessor.enable_dither = true;
		}

		// set pipeline shader program parameters
		// explicitly specify the resource parameter uses
		// you can also change these when rendering
		/*auto& _program = _gpp->program();
		_program.invoke_uniform_block("wait");
		_program.invoke_shader_storage_block("");
		_program.invoke_atomic_uint("");*/

		// you can reallocate or fill vertex attributes, indices, instance attributes
		// all data format are fixed after initialization, only thing you can changed only number of these attribs

		// set pipeline render target
		// default : global device framebuffer
		// custom framebuffer : you can operate every component of it
		// you can also change it when rendering

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
	return false;
}

bool gl_scene_renderer::hibernate() noexcept
{
	return false;
}

void gl_scene_renderer::render(float delta_time) noexcept
{
	if (_gpp && _cpp && _mpp)
	{
		default_framebuffer->set_color_cache(0.0f + delta_time, 0.0f, 0.0f, 1.0f);
		default_framebuffer->switch_draw_buffer(gl_default_framebuffer_draw_buffer::LEFT);
		default_framebuffer->clear_color_buffer();
#ifdef _DEBUG
		if (!_gpp) throw std::exception("mesh pipeline must not be null");
#endif
		_gpp->enable();
		//_gpp->unsyncable_draw_arrays(0, 1024);
		_gpp->disable();
	}
}

bool gl_scene_renderer::wake() noexcept
{
	return false;
}

bool gl_scene_renderer::detach() noexcept
{
	if (_gpp && _cpp && _mpp)
	{
		_gpp.release();
		_cpp.release();
		_mpp.release();
		return true;
	}
	return false;
}

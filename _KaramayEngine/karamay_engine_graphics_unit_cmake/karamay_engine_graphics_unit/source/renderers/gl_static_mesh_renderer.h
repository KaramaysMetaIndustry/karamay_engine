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
		if (!_vp_pipeline->load("C:/PrivateRepos/karamay_engine/_KaramayEngine/karamay_engine_graphics_unit_cmake/karamay_engine_graphics_unit/shaders/renderers/static_mesh_renderer/mesh_pp")) return false;
		
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
		default_framebuffer->set_color_cache(0.0f + delta_time, 0.0f, 0.0f, 1.0f);
		default_framebuffer->switch_draw_buffer(gl_default_framebuffer_draw_buffer::LEFT);
		default_framebuffer->clear_color_buffer();
		std::cout << delta_time << std::endl;
	#ifdef _DEBUG
		if (!_vp_pipeline) throw std::exception("mesh pipeline must not be null");
	#endif
		_vp_pipeline->enable();
		_vp_pipeline->unsyncable_draw_arrays(0, 1024);
		_vp_pipeline->disable();
	}

DEFINE_RENDERER_END



//
//void test1()
//{
//	glfw_window* window = new glfw_window();
//	window->load_context();
//
//	glewInit();
//
//
//	/*auto ubod = std::make_shared<gl_uniform_buffer_descriptor>();
//
//	ubod->add_uniform(glm::vec4(0.0f, 1.0f, 0.5f, 0.0f));
//	ubod->add_uniform(glm::vec3(1.2f, 1.6f, 0.7f));
//	ubod->add_uniform(glm::mat4(0.0f));*/
//
//
//	//std::uint8_t* data = (std::uint8_t*)ubod->get_data();
//	//
//	//glm::vec3* d = (glm::vec3*)(data + 16);
//
//	/*const void* _data = vao->get_mapped_data();
//	const glv_vec3* _dv = (glv_vec3*)_data;
//	for (int i = 0; i < 36; ++i)
//	{
//		std::cout << _dv[i].r << "," << _dv[i].g << "," << _dv[i].b << std::endl;
//	}*/
//
//
//	//std::cout << "size :" << vao->get_attribute_components_num(0) << std::endl;
//	//std::cout << "size :" << vao->get_attribute_components_num(1) << std::endl;
//	//std::cout << "size :" << vao->get_attribute_components_num(2) << std::endl;
//
//
//	// camera / view_matrix/ camera_position
//	auto camera = std::make_shared<gl_camera>();
//
//	// model_matrix
//	glm::vec3 Position = glm::vec3(0.0f, 0.0f, 0.0f);
//	float Pitch, Yaw, Roll;
//	Pitch = Yaw = Roll = 0.0f;
//	glm::mat4 model_mat(1.0f);
//	model_mat = glm::translate(model_mat, Position);
//	model_mat = glm::rotate(model_mat, glm::radians(Pitch), glm::vec3(1.0f, 0.0f, 0.0f));
//	model_mat = glm::rotate(model_mat, glm::radians(Yaw), glm::vec3(0.0f, 1.0f, 0.0f));
//	model_mat = glm::rotate(model_mat, glm::radians(Roll), glm::vec3(0.0f, 0.0f, 1.0f));
//	// projection_matrix
//	glm::mat4 proj_matrix
//		= glm::perspective(glm::radians(45.0f),
//			(float)window->get_framebuffer_width() / (float)window->get_framebuffer_height(),
//			0.1f, 40.0f);
//
//
//	// uniforms
//	auto camera_position
//		= std::make_shared<gl_variable<glv_vec3>>("camera_position", camera->get_position());
//	auto projection_matrix
//		= std::make_shared<gl_variable<glv_mat4>>("projection_matrix", proj_matrix);
//	auto model_matrix
//		= std::make_shared<gl_variable<glv_mat4>>("model_matrix", model_mat);
//	auto view_matrix
//		= std::make_shared<gl_variable<glv_mat4>>("view_matirx", camera->get_view_matrix());
//
//	auto ambient_light
//		= std::make_shared<gl_variable<glv_vec3>>("en_lights.ambient_light", glv_vec3());
//
//	auto directional_light
//		= std::make_shared<gl_variable<glv_vec3>>("en_lights.directional_light[0]", glv_vec3());
//
//	/*auto directional_lights_num = std::make_shared< gl_variable<glv_int>>();
//
//	auto point_light = std::make_shared< gl_variable<glv_vec3>>();
//	auto point_lights_num = std::make_shared< gl_variable<glv_int>>();
//
//	auto spot_light = std::make_shared< gl_variable<glv_vec3>>();
//	auto spot_lights_num = std::make_shared< gl_variable<glv_int>>();*/
//
//	// textures
//	auto container2 = std::make_shared<gl_texture_2d>();
//	auto albedo_map = std::make_shared<gl_texture_2d>();
//	auto normal_map = std::make_shared<gl_texture_2d>();
//	//auto metalness_map = std::make_shared<gl_texture_2d>();
//	auto roughness_map = std::make_shared<gl_texture_2d>();
//	auto displacement_map = std::make_shared<gl_texture_2d>();
//	auto ambient_occlusion_map = std::make_shared<gl_texture_2d>();
//
//	/*gl_texture_pixels container2_pixels("assets/Textures/container2.png");
//	container2->fill(container2_pixels.width, container2_pixels.height, container2_pixels.format, (const void*)container2_pixels.pixels);
//	container2->set_name("container2");*/
//
//	gl_texture_pixels albedo_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_Color.jpg");
//	albedo_map->fill(albedo_pixels.width, albedo_pixels.height, albedo_pixels.format, (const void*)albedo_pixels.pixels);
//	albedo_map->set_name("mat.albedo_map");
//
//	gl_texture_pixels normal_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_Normal.jpg");
//	normal_map->fill(normal_pixels.width, normal_pixels.height, normal_pixels.format, (const void*)normal_pixels.pixels);
//	normal_map->set_name("mat.normal_map");
//
//	/*gl_texture_pixels metalness_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_.jpg");
//	metalness_map->fill(metalness_pixels.width, metalness_pixels.height, (const void*)metalness_pixels.pixels);
//	metalness_map->set_name("mat.metalness_map");*/
//
//	gl_texture_pixels roughness_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_Roughness.jpg");
//	roughness_map->fill(roughness_pixels.width, roughness_pixels.height, roughness_pixels.format, (const void*)roughness_pixels.pixels);
//	roughness_map->set_name("mat.roughness_map");
//
//	gl_texture_pixels displacement_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_Displacement.jpg");
//	displacement_map->fill(displacement_pixels.width, displacement_pixels.height, displacement_pixels.format, (const void*)displacement_pixels.pixels);
//	displacement_map->set_name("mat.displacement_map");
//
//	gl_texture_pixels ambient_occlusion_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_AmbientOcclusion.jpg");
//	ambient_occlusion_map->fill(ambient_occlusion_pixels.width, ambient_occlusion_pixels.height, ambient_occlusion_pixels.format, (const void*)ambient_occlusion_pixels.pixels);
//	ambient_occlusion_map->set_name("mat.ambient_occlusion_map");
//
//
//	glViewport(0, 0, window->get_framebuffer_width(), window->get_framebuffer_height());
//
//	/*std::vector<glv_vec3> poss{
//		glv_vec3(0.5f, 0.5f, 0.0f),
//		glv_vec3(0.5f, -0.5f, 0.0f),
//		glv_vec3(-0.5f, -0.5f, 0.0f),
//		glv_vec3(-0.5f, 0.5f, 0.0f)
//	};
//
//	std::vector<glv_vec2> uvss{
//		glv_vec2(1.0f, 1.0f),
//		glv_vec2(1.0f, 0.0f),
//		glv_vec2(0.0f, 0.0f),
//		glv_vec2(0.0f, 1.0f)
//	};
//
//	std::vector<glm::uint32> indices{
//		0, 1, 3,
//		1, 2, 3
//	};*/
//
//	std::size_t size = positions.size();
//
//	// vertex array
//	auto vaod = sptr(gl_vertex_array_descriptor);
//	//vaod->add_attributes<glv_vec3>(poss);
//	//vaod->add_attributes<glv_vec2>(uvss);
//	vaod->add_attributes<glv_vec3>(positions);
//	vaod->add_attributes<glv_vec2>(uvs);
//	vaod->add_attributes<glv_vec3>(normals);
//	auto vao = sp_vertex_array(vaod);
//
//	// element array
//	/*auto ebod = std::make_shared<gl_element_array_buffer_descriptor>();
//	ebod->set_indices(indices);
//	auto ebo = std::make_shared<gl_element_array_buffer>();
//	ebo->fill(ebod);*/
//
//	// program
//	auto program = std::make_shared<gl_program>();
//	/*program->construct({
//		"shaders/test.vert",
//		"shaders/test.frag" });*/
//	program->construct({
//		"shaders/Mesh/PBRMesh/PBRMesh.vert",
//		"shaders/Mesh/PBRMesh/PBRMesh.tesc",
//		"shaders/Mesh/PBRMesh/PBRMesh.tese",
//		"shaders/Mesh/PBRMesh/PBRMesh.geom",
//		"shaders/Mesh/PBRMesh/PBRMesh.frag" });
//	// ...
//	program->set_vertex_array(vao);
//	// ...
//	program->add_texture(albedo_map);
//	program->add_texture(normal_map);
//	program->add_texture(roughness_map);
//	program->add_texture(displacement_map);
//	program->add_texture(ambient_occlusion_map);
//	// ...
//	program->add_uniform(camera_position);
//	program->add_uniform(projection_matrix);
//	program->add_uniform(view_matrix);
//	program->add_uniform(model_matrix);
//	// ...
//	program->set_framebuffer();
//	program->set_commands([&size] {
//		//glDrawArrays(GL_TRIANGLES, 0, 5);
//		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
//
//		glPatchParameteri(GL_PATCH_VERTICES, 3);
//		glDrawArraysInstancedBaseInstance(GL_PATCHES, 0, size, 1, 0);
//		});
//
//
//	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_FILL GL_POINT
//	//glFrontFace(GL_CW);//default ��ʱ�� GL_CW ˳ʱ��
//
//	//glEnable(GL_COLOR_BUFFER_BIT);
//	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//
//	//glEnable(GL_ACCUM_BUFFER_BIT);
//	//glClearAccum(1.0f, 0.2f, 1.0f, 1.0f);
//
//	// when current frag-z < 1.0, keep it
//	// fragShader write its z value before working
//	//glEnable(GL_DEPTH_TEST);
//	//glDepthFunc(GL_LESS);
//	//glDepthMask(GL_TRUE);
//	//glClearDepth(1.0f);
//
//	//glEnable(GL_STENCIL_TEST);
//	//glStencilFunc(GL_ALWAYS, 1, 0xFF);
//	//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
//	//glStencilMask(GL_TRUE);
//	//glClearStencil(0);
//
//
//
//	int i = 1;
//	while (i--)
//	{
//
//		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//		glClear(GL_COLOR_BUFFER_BIT);
//		program->render(0.0f);
//		window->tick(0.0f);
//	}
//}



#endif
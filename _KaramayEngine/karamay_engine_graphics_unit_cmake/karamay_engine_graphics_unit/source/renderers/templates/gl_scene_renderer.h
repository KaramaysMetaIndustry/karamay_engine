#ifndef GL_SCENE_RENDERER_H
#define GL_SCENE_RENDERER_H
#include "graphics/opengl/renderer/gl_renderer.h"

class gl_scene_renderer : public gl_renderer
{
private:

	static gl_scene_renderer* _instance;

	gl_scene_renderer() = default;

public:

	static gl_scene_renderer* invoke() noexcept
	{
		if (!_instance)
		{
			_instance = new gl_scene_renderer();
		}
		return _instance;
	}

private:

	std::unique_ptr<gl_graphics_pipeline> _gpp;

	std::unique_ptr<gl_compute_pipeline> _cpp;
	
	std::unique_ptr<gl_mesh_pipeline> _mpp;

public:

	bool initialize() noexcept override;

	bool attach() noexcept override;

	bool hibernate() noexcept override;

	void render(float delta_time) noexcept override;

	bool wake() noexcept override;

	bool detach() noexcept override;

};



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
//	//glFrontFace(GL_CW);
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



#endif
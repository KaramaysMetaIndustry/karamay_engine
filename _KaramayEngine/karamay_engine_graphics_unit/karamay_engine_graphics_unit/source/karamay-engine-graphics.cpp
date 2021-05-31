
#include "graphics/program/gl_program.h"
#include "graphics/variable/gl_variable.h"
#include "graphics/buffer/customization/gl_element_array_buffer.h"
#include "graphics/vertex_array/gl_vertex_array.h"
#include "graphics/variable/gl_variable.h"
#include "window/window.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../dependencies/stb_image.h"

float vertices[] = {
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f, //0
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f //35
};

std::uint32_t indices[] = 
{
	1, 2, 2, 3, 4, 5, 6
};

std::vector<glv_vec3> offset_positions{
	glv_vec3(0.0f,  0.0f,  0.0f),
	glv_vec3(2.0f,  5.0f, -15.0f),
	glv_vec3(-1.5f, -2.2f, -2.5f),
	glv_vec3(-3.8f, -2.0f, -12.3f),
	glv_vec3(2.4f, -0.4f, -3.5f),
	glv_vec3(-1.7f,  3.0f, -7.5f),
	glv_vec3(1.3f, -2.0f, -2.5f),
	glv_vec3(1.5f,  2.0f, -2.5f),
	glv_vec3(1.5f,  0.2f, -1.5f),
	glv_vec3(-1.3f,  1.0f, -1.5f)
};

std::vector<glv_vec3> normals{
		glv_vec3(0.0f, 0.0f, -1.0f),
		glv_vec3(0.0f, 0.0f, -1.0f),
		glv_vec3(0.0f, 0.0f, -1.0f),
		glv_vec3(0.0f, 0.0f, -1.0f),
		glv_vec3(0.0f, 0.0f, -1.0f),
		glv_vec3(0.0f, 0.0f, -1.0f),

		glv_vec3(0.0f, 0.0f, 1.0f),
		glv_vec3(0.0f, 0.0f, 1.0f),
		glv_vec3(0.0f, 0.0f, 1.0f),
		glv_vec3(0.0f, 0.0f, 1.0f),
		glv_vec3(0.0f, 0.0f, 1.0f),
		glv_vec3(0.0f, 0.0f, 1.0f),

		glv_vec3(-1.0f, 0.0f, 0.0f),
		glv_vec3(-1.0f, 0.0f, 0.0f),
		glv_vec3(-1.0f, 0.0f, 0.0f),
		glv_vec3(-1.0f, 0.0f, 0.0f),
		glv_vec3(-1.0f, 0.0f, 0.0f),
		glv_vec3(-1.0f, 0.0f, 0.0f),

		glv_vec3(1.0f, 0.0f, 0.0f),
		glv_vec3(1.0f, 0.0f, 0.0f),
		glv_vec3(1.0f, 0.0f, 0.0f),
		glv_vec3(1.0f, 0.0f, 0.0f),
		glv_vec3(1.0f, 0.0f, 0.0f),
		glv_vec3(1.0f, 0.0f, 0.0f),

		glv_vec3(0.0f, -1.0f, 0.0f),
		glv_vec3(0.0f, -1.0f, 0.0f),
		glv_vec3(0.0f, -1.0f, 0.0f),
		glv_vec3(0.0f, -1.0f, 0.0f),
		glv_vec3(0.0f, -1.0f, 0.0f),
		glv_vec3(0.0f, -1.0f, 0.0f),

		glv_vec3(0.0f, 1.0f, 0.0f),
		glv_vec3(0.0f, 1.0f, 0.0f),
		glv_vec3(0.0f, 1.0f, 0.0f),
		glv_vec3(0.0f, 1.0f, 0.0f),
		glv_vec3(0.0f, 1.0f, 0.0f),
		glv_vec3(0.0f, 1.0f, 0.0f),
};

std::vector<glv_vec2> uvs{
		glv_vec2(0.0f, 0.0f),
		glv_vec2(1.0f,  0.0f),
		glv_vec2(1.0f,  1.0f),
		glv_vec2(1.0f,  1.0f),
		glv_vec2(0.0f,  1.0f),
		glv_vec2(0.0f,  0.0f),

		glv_vec2(0.0f,  0.0f),
		glv_vec2(1.0f,  0.0f),
		glv_vec2(1.0f,  1.0f),
		glv_vec2(1.0f,  1.0f),
		glv_vec2(0.0f,  1.0f),
		glv_vec2(0.0f,  0.0f),

		glv_vec2(1.0f,  0.0f),
		glv_vec2(1.0f,  1.0f),
		glv_vec2(0.0f,  1.0f),
		glv_vec2(0.0f,  1.0f),
		glv_vec2(0.0f,  0.0f),
		glv_vec2(1.0f,  0.0f),

		glv_vec2(1.0f,  0.0f),
		glv_vec2(1.0f,  1.0f),
		glv_vec2(0.0f,  1.0f),
		glv_vec2(0.0f,  1.0f),
		glv_vec2(0.0f,  0.0f),
		glv_vec2(1.0f,  0.0f),

		glv_vec2(0.0f,  1.0f),
		glv_vec2(1.0f,  1.0f),
		glv_vec2(1.0f,  0.0f),
		glv_vec2(1.0f,  0.0f),
		glv_vec2(0.0f,  0.0f),
		glv_vec2(0.0f,  1.0f),

		glv_vec2(0.0f,  1.0f),
		glv_vec2(1.0f,  1.0f),
		glv_vec2(1.0f,  0.0f),
		glv_vec2(1.0f,  0.0f),
		glv_vec2(0.0f,  0.0f),
		glv_vec2(0.0f,  1.0f)
};

std::vector<glv_vec3> positions{
		glv_vec3(-0.5f, -0.5f, -0.5f),
		glv_vec3( 0.5f, -0.5f, -0.5f),
		glv_vec3( 0.5f,  0.5f, -0.5f),
		glv_vec3( 0.5f,  0.5f, -0.5f),
		glv_vec3(-0.5f,  0.5f, -0.5f),
		glv_vec3(-0.5f, -0.5f, -0.5f),

		glv_vec3(-0.5f, -0.5f,  0.5f),
		glv_vec3( 0.5f, -0.5f,  0.5f),
		glv_vec3( 0.5f,  0.5f,  0.5f),
		glv_vec3( 0.5f,  0.5f,  0.5f),
		glv_vec3(-0.5f,  0.5f,  0.5f),
		glv_vec3(-0.5f, -0.5f,  0.5f),

		glv_vec3(-0.5f,  0.5f,  0.5f),
		glv_vec3(-0.5f,  0.5f, -0.5f),
		glv_vec3(-0.5f, -0.5f, -0.5f),
		glv_vec3(-0.5f, -0.5f, -0.5f),
		glv_vec3(-0.5f, -0.5f,  0.5f),
		glv_vec3(-0.5f,  0.5f,  0.5f),

		glv_vec3( 0.5f,  0.5f,  0.5f),
		glv_vec3( 0.5f,  0.5f, -0.5f),
		glv_vec3( 0.5f, -0.5f, -0.5f),
		glv_vec3( 0.5f, -0.5f, -0.5f),
		glv_vec3( 0.5f, -0.5f,  0.5f),
		glv_vec3( 0.5f,  0.5f,  0.5f),

		glv_vec3(-0.5f, -0.5f, -0.5f),
		glv_vec3( 0.5f, -0.5f, -0.5f),
		glv_vec3( 0.5f, -0.5f,  0.5f),
		glv_vec3( 0.5f, -0.5f,  0.5f),
		glv_vec3(-0.5f, -0.5f,  0.5f),
		glv_vec3(-0.5f, -0.5f, -0.5f),

		glv_vec3(-0.5f,  0.5f, -0.5f),
		glv_vec3( 0.5f,  0.5f, -0.5f),
		glv_vec3( 0.5f,  0.5f,  0.5f),
		glv_vec3( 0.5f,  0.5f,  0.5f),
		glv_vec3(-0.5f,  0.5f,  0.5f),
		glv_vec3(-0.5f,  0.5f, -0.5f)
};

#define sptr(T)\
std::make_shared<##T##>()\

#define uptr(T)\
std::make_unique<##T##>()\

template<typename T>
std::weak_ptr<T> make_weak(std::shared_ptr<T> sptr)
{
	return std::weak_ptr<T>(sptr);
}

#define wptr(sptr)\
make_weak(sptr)\




struct gl_texture_pixels
{
	stbi_uc* pixels;

	std::int32_t width, height;

	std::uint32_t format;


	gl_texture_pixels(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(true);
		std::int32_t _channels = 0;
		pixels = stbi_load(path.c_str(), &width, &height, &_channels, 0);

		std::cout << "channels: " << _channels << std::endl;

		if (pixels == nullptr) {
			std::cout << "load fail" << std::endl;
		}

		switch (_channels)
		{
		case 1: format = GL_RED; break;
		case 3:	format = GL_RGB;  break;
		case 4: format = GL_RGBA; break;
		default:
			break;
		}
	}
};

int main()
{
  
	glfw_window* window = new glfw_window();
	window->load_context();

	glewInit();



	/*auto ubod = std::make_shared<gl_uniform_buffer_descriptor>();
	
	ubod->add_uniform(glm::vec4(0.0f, 1.0f, 0.5f, 0.0f));
	ubod->add_uniform(glm::vec3(1.2f, 1.6f, 0.7f));
	ubod->add_uniform(glm::mat4(0.0f));*/


	//std::uint8_t* data = (std::uint8_t*)ubod->get_data();
	//
	//glm::vec3* d = (glm::vec3*)(data + 16);

	
	


	
	auto vaod = sptr(gl_vertex_array_descriptor);
  	vaod->add_attributes<glv_vec3>(positions);
	vaod->add_attributes<glv_vec2>(uvs);
	vaod->add_attributes<glv_vec3>(normals);
	auto vao = sptr(gl_vertex_array);
	vao->fill(vaod);

	/*const void* _data = vao->get_mapped_data();
	const glv_vec3* _dv = (glv_vec3*)_data;
	for (int i = 0; i < 36; ++i)
	{
		std::cout << _dv[i].r << "," << _dv[i].g << "," << _dv[i].b << std::endl;
	}*/


	//std::cout << "size :" << vao->get_attribute_components_num(0) << std::endl;
	//std::cout << "size :" << vao->get_attribute_components_num(1) << std::endl;
	//std::cout << "size :" << vao->get_attribute_components_num(2) << std::endl;
	auto camera_position = std::make_shared<gl_variable<glv_vec3>>();
	auto projection_matrix = std::make_shared<gl_variable<glv_mat4>>();
	auto model_matrix = std::make_shared<gl_variable<glv_mat4>>();
	auto view_matrix = std::make_shared<gl_variable<glv_mat4>>();
	camera_position->name = "camera_position";
	camera_position->value = glv_vec3(0.0f, 0.0f, 0.0f);
	projection_matrix->name = "projection_matrix";
	projection_matrix->value = glv_mat4(0.0f);
	model_matrix->name = "model_matrix";
	model_matrix->value = glv_mat4(0.0f);
	view_matrix->name = "view_matirx";
	view_matrix->value = glv_mat4(0.0f);

	auto ambient_light = std::make_shared<gl_variable<glv_vec3>>();
	ambient_light->name = "en_lights.ambient_light";

	auto directional_light = std::make_shared< gl_variable<glv_vec3>>();
	directional_light->name = "en_lights.directional_light[0]";
	
	auto directional_lights_num = std::make_shared< gl_variable<glv_int>>();

	auto point_light = std::make_shared< gl_variable<glv_vec3>>();
	auto point_lights_num = std::make_shared< gl_variable<glv_int>>();

	auto spot_light = std::make_shared< gl_variable<glv_vec3>>();
	auto spot_lights_num = std::make_shared< gl_variable<glv_int>>();

	auto albedo_map = std::make_shared<gl_texture_2d>();
	auto normal_map = std::make_shared<gl_texture_2d>();
	//auto metalness_map = std::make_shared<gl_texture_2d>();
	auto roughness_map = std::make_shared<gl_texture_2d>();
	auto displacement_map = std::make_shared<gl_texture_2d>();
	auto ambient_occlusion_map = std::make_shared<gl_texture_2d>();
	
	gl_texture_pixels albedo_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_Color.jpg");
	albedo_map->fill(albedo_pixels.width, albedo_pixels.height, albedo_pixels.format, (const void*)albedo_pixels.pixels);
	albedo_map->set_name("mat.albedo_map");

	gl_texture_pixels normal_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_Normal.jpg");
	normal_map->fill(normal_pixels.width, normal_pixels.height, normal_pixels.format, (const void*)normal_pixels.pixels);
	normal_map->set_name("mat.normal_map");

	/*gl_texture_pixels metalness_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_.jpg");
	metalness_map->fill(metalness_pixels.width, metalness_pixels.height, (const void*)metalness_pixels.pixels);
	metalness_map->set_name("mat.metalness_map");*/

	gl_texture_pixels roughness_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_Roughness.jpg");
	roughness_map->fill(roughness_pixels.width, roughness_pixels.height, roughness_pixels.format, (const void*)roughness_pixels.pixels);
	roughness_map->set_name("mat.roughness_map");

	gl_texture_pixels displacement_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_Displacement.jpg");
	displacement_map->fill(displacement_pixels.width, displacement_pixels.height, displacement_pixels.format, (const void*)displacement_pixels.pixels);
	displacement_map->set_name("mat.displacement_map");

	gl_texture_pixels ambient_occlusion_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_AmbientOcclusion.jpg");
	ambient_occlusion_map->fill(ambient_occlusion_pixels.width, ambient_occlusion_pixels.height, ambient_occlusion_pixels.format, (const void*)ambient_occlusion_pixels.pixels);
	ambient_occlusion_map->set_name("mat.ambient_occlusion_map");

	auto program = std::make_shared<gl_program>();
	program->construct({ 
		"shaders/Mesh/PBRMesh/PBRMesh.vert", 
		"shaders/Mesh/PBRMesh/PBRMesh.tesc", 
		"shaders/Mesh/PBRMesh/PBRMesh.tese", 
		"shaders/Mesh/PBRMesh/PBRMesh.geom",
		"shaders/Mesh/PBRMesh/PBRMesh.frag" });
	// ...
	program->set_vertex_array(vao);	
	// ...
	program->add_texture(albedo_map);
	program->add_texture(normal_map);
	program->add_texture(roughness_map);
	program->add_texture(displacement_map);
	program->add_texture(ambient_occlusion_map);
	// ...
	program->add_uniform(camera_position);
	program->add_uniform(projection_matrix);
	program->add_uniform(view_matrix);
	program->add_uniform(model_matrix);
	// ...
	program->set_framebuffer();
	// ...
	program->set_commands([] {
		
		});

	program->render(0.0f);
}

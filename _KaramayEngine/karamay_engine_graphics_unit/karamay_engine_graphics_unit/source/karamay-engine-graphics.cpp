
#include "graphics/program/gl_program.h"
#include "graphics/variable/gl_variable.h"
#include "graphics/buffer/customization/gl_element_array_buffer.h"
#include "graphics/vertex_array/gl_vertex_array.h"
#include "graphics/camera/gl_camera.h"



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

std::uint32_t indices[] = {
	1, 2, 2, 3, 4, 5, 6
};

std::vector<glv_f32vec3> offset_positions{
	glv_f32vec3(0.0f,  0.0f,  0.0f),
	glv_f32vec3(2.0f,  5.0f, -15.0f),
	glv_f32vec3(-1.5f, -2.2f, -2.5f),
	glv_f32vec3(-3.8f, -2.0f, -12.3f),
	glv_f32vec3(2.4f, -0.4f, -3.5f),
	glv_f32vec3(-1.7f,  3.0f, -7.5f),
	glv_f32vec3(1.3f, -2.0f, -2.5f),
	glv_f32vec3(1.5f,  2.0f, -2.5f),
	glv_f32vec3(1.5f,  0.2f, -1.5f),
	glv_f32vec3(-1.3f,  1.0f, -1.5f)
};

std::vector<glv_f32vec3> normals{
		glv_f32vec3(0.0f, 0.0f, -1.0f),
		glv_f32vec3(0.0f, 0.0f, -1.0f),
		glv_f32vec3(0.0f, 0.0f, -1.0f),
		glv_f32vec3(0.0f, 0.0f, -1.0f),
		glv_f32vec3(0.0f, 0.0f, -1.0f),
		glv_f32vec3(0.0f, 0.0f, -1.0f),

		glv_f32vec3(0.0f, 0.0f, 1.0f),
		glv_f32vec3(0.0f, 0.0f, 1.0f),
		glv_f32vec3(0.0f, 0.0f, 1.0f),
		glv_f32vec3(0.0f, 0.0f, 1.0f),
		glv_f32vec3(0.0f, 0.0f, 1.0f),
		glv_f32vec3(0.0f, 0.0f, 1.0f),

		glv_f32vec3(-1.0f, 0.0f, 0.0f),
		glv_f32vec3(-1.0f, 0.0f, 0.0f),
		glv_f32vec3(-1.0f, 0.0f, 0.0f),
		glv_f32vec3(-1.0f, 0.0f, 0.0f),
		glv_f32vec3(-1.0f, 0.0f, 0.0f),
		glv_f32vec3(-1.0f, 0.0f, 0.0f),

		glv_f32vec3(1.0f, 0.0f, 0.0f),
		glv_f32vec3(1.0f, 0.0f, 0.0f),
		glv_f32vec3(1.0f, 0.0f, 0.0f),
		glv_f32vec3(1.0f, 0.0f, 0.0f),
		glv_f32vec3(1.0f, 0.0f, 0.0f),
		glv_f32vec3(1.0f, 0.0f, 0.0f),

		glv_f32vec3(0.0f, -1.0f, 0.0f),
		glv_f32vec3(0.0f, -1.0f, 0.0f),
		glv_f32vec3(0.0f, -1.0f, 0.0f),
		glv_f32vec3(0.0f, -1.0f, 0.0f),
		glv_f32vec3(0.0f, -1.0f, 0.0f),
		glv_f32vec3(0.0f, -1.0f, 0.0f),

		glv_f32vec3(0.0f, 1.0f, 0.0f),
		glv_f32vec3(0.0f, 1.0f, 0.0f),
		glv_f32vec3(0.0f, 1.0f, 0.0f),
		glv_f32vec3(0.0f, 1.0f, 0.0f),
		glv_f32vec3(0.0f, 1.0f, 0.0f),
		glv_f32vec3(0.0f, 1.0f, 0.0f),
};

std::vector<glv_f32vec2> uvs{
		glv_f32vec2(0.0f, 0.0f),
		glv_f32vec2(1.0f,  0.0f),
		glv_f32vec2(1.0f,  1.0f),
		glv_f32vec2(1.0f,  1.0f),
		glv_f32vec2(0.0f,  1.0f),
		glv_f32vec2(0.0f,  0.0f),

		glv_f32vec2(0.0f,  0.0f),
		glv_f32vec2(1.0f,  0.0f),
		glv_f32vec2(1.0f,  1.0f),
		glv_f32vec2(1.0f,  1.0f),
		glv_f32vec2(0.0f,  1.0f),
		glv_f32vec2(0.0f,  0.0f),

		glv_f32vec2(1.0f,  0.0f),
		glv_f32vec2(1.0f,  1.0f),
		glv_f32vec2(0.0f,  1.0f),
		glv_f32vec2(0.0f,  1.0f),
		glv_f32vec2(0.0f,  0.0f),
		glv_f32vec2(1.0f,  0.0f),

		glv_f32vec2(1.0f,  0.0f),
		glv_f32vec2(1.0f,  1.0f),
		glv_f32vec2(0.0f,  1.0f),
		glv_f32vec2(0.0f,  1.0f),
		glv_f32vec2(0.0f,  0.0f),
		glv_f32vec2(1.0f,  0.0f),

		glv_f32vec2(0.0f,  1.0f),
		glv_f32vec2(1.0f,  1.0f),
		glv_f32vec2(1.0f,  0.0f),
		glv_f32vec2(1.0f,  0.0f),
		glv_f32vec2(0.0f,  0.0f),
		glv_f32vec2(0.0f,  1.0f),

		glv_f32vec2(0.0f,  1.0f),
		glv_f32vec2(1.0f,  1.0f),
		glv_f32vec2(1.0f,  0.0f),
		glv_f32vec2(1.0f,  0.0f),
		glv_f32vec2(0.0f,  0.0f),
		glv_f32vec2(0.0f,  1.0f)
};

std::vector<glv_f32vec3> positions{
		glv_f32vec3(-0.5f, -0.5f, -0.5f),
		glv_f32vec3( 0.5f, -0.5f, -0.5f),
		glv_f32vec3( 0.5f,  0.5f, -0.5f),
		glv_f32vec3( 0.5f,  0.5f, -0.5f),
		glv_f32vec3(-0.5f,  0.5f, -0.5f),
		glv_f32vec3(-0.5f, -0.5f, -0.5f),

		glv_f32vec3(-0.5f, -0.5f,  0.5f),
		glv_f32vec3( 0.5f, -0.5f,  0.5f),
		glv_f32vec3( 0.5f,  0.5f,  0.5f),
		glv_f32vec3( 0.5f,  0.5f,  0.5f),
		glv_f32vec3(-0.5f,  0.5f,  0.5f),
		glv_f32vec3(-0.5f, -0.5f,  0.5f),

		glv_f32vec3(-0.5f,  0.5f,  0.5f),
		glv_f32vec3(-0.5f,  0.5f, -0.5f),
		glv_f32vec3(-0.5f, -0.5f, -0.5f),
		glv_f32vec3(-0.5f, -0.5f, -0.5f),
		glv_f32vec3(-0.5f, -0.5f,  0.5f),
		glv_f32vec3(-0.5f,  0.5f,  0.5f),

		glv_f32vec3( 0.5f,  0.5f,  0.5f),
		glv_f32vec3( 0.5f,  0.5f, -0.5f),
		glv_f32vec3( 0.5f, -0.5f, -0.5f),
		glv_f32vec3( 0.5f, -0.5f, -0.5f),
		glv_f32vec3( 0.5f, -0.5f,  0.5f),
		glv_f32vec3( 0.5f,  0.5f,  0.5f),

		glv_f32vec3(-0.5f, -0.5f, -0.5f),
		glv_f32vec3( 0.5f, -0.5f, -0.5f),
		glv_f32vec3( 0.5f, -0.5f,  0.5f),
		glv_f32vec3( 0.5f, -0.5f,  0.5f),
		glv_f32vec3(-0.5f, -0.5f,  0.5f),
		glv_f32vec3(-0.5f, -0.5f, -0.5f),

		glv_f32vec3(-0.5f,  0.5f, -0.5f),
		glv_f32vec3( 0.5f,  0.5f, -0.5f),
		glv_f32vec3( 0.5f,  0.5f,  0.5f),
		glv_f32vec3( 0.5f,  0.5f,  0.5f),
		glv_f32vec3(-0.5f,  0.5f,  0.5f),
		glv_f32vec3(-0.5f,  0.5f, -0.5f)
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

		//std::cout << "channels: " << _channels << std::endl;

		if (pixels == nullptr) {
			std::cout << "load fail" << std::endl;
		}

		switch (_channels)
		{
		case 1: format = GL_RED; break;
		case 3:	format = GL_RGB; break;
		case 4: format = GL_RGBA; break;
		default:
			break;
		}
	}
};

void test0();

int main()
{


	//std::cout << "size: " << sizeof(bool) << std::endl;
	/*std::cout << "weak ptr size: " << sizeof(std::weak_ptr<std::string>) << std::endl;
	std::cout << "unique ptr size: " << sizeof(std::unique_ptr<std::string>) << std::endl;
  
	std::cout << "ori ptr size: " << sizeof(std::string*) << std::endl;*/


	test0();
}


template<typename T>
std::string get_uniform_type_str()
{
	return "";
}

template<>
std::string get_uniform_type_str<glu_f32vec1::value_type>()
{
	return "float";
}

template<>
std::string get_uniform_type_str<glu_f64vec1::value_type>()
{
	return "double";
}

template<>
std::string get_uniform_type_str<glu_i32vec1::value_type>()
{
	return "int";
}

template<>
std::string get_uniform_type_str<glu_ui32vec1::value_type>()
{
	return "uint";
}

template<typename T>
auto create_uniform(const std::string& name, const T& value)
{
	const std::uint8_t* _value_ptr = reinterpret_cast<const std::uint8_t*>(&value);
	std::vector<std::uint8_t> _stream(_value_ptr, _value_ptr + sizeof(T));
	const std::string type = get_uniform_type_str<T::value_type>();
	return std::make_shared<gl_variable>(type, name, _stream);
}


auto string_to_stream(const std::string& type, const std::string& name, const std::string value)
{

	std::vector<std::uint8_t> stream;
	return std::make_shared<gl_variable>(type, name, stream);
}

void test0()
{
	glfw_window* window = new glfw_window();
	window->load_context();
	
	std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;
	glewInit();

	glViewport(0, 0, window->get_framebuffer_width(), window->get_framebuffer_height());


	std::vector<glv_f32vec3> positions{
		glv_f32vec3(0.5f, 0.5f, 0.0f),
		glv_f32vec3(0.5f, -0.5f, 0.0f),
		glv_f32vec3(-0.5f, -0.5f, 0.0f),
		glv_f32vec3(-0.5f, 0.5f, 0.0f)
	};

	std::vector<glv_f32vec2> uvs{
		glv_f32vec2(1.0f, 1.0f),
		glv_f32vec2(1.0f, 0.0f),
		glv_f32vec2(0.0f, 0.0f),
		glv_f32vec2(0.0f, 1.0f)
	};

	std::vector<glm::i16vec4> tests{
		glm::i16vec4(1, 0, 0, 1),
		glm::i16vec4(0, 1, 0, 1),
		glm::i16vec4(0, 0, 1, 1),
		glm::i16vec4(0, 1, 0, 1)
	};

	std::vector<glm::uint32> indices{
		0, 1, 3, // polygon0
		1, 2, 3 // polygon1
	};

	// 默认按column存
// 除了单精度浮点数，其他类型顶点数据在frag中声明时，必须使用flat标识，
// 并且所有片段拿到的改顶点值等于最后一个顶点的值
//std::vector<glv_dmat4> tests{
//	glv_dmat4(
//	0, 1, 1, 0, // column
//	1, 0, 0, 0,// column
//	0, 1, 1, 0,// column
//	0, 0, 0, 1),// column
//	glv_dmat4(
//	0, 1, 1, 0,
//	1, 0, 0, 0,
//	0, 1, 1, 0,
//	0, 0, 0, 1),
//	glv_dmat4(
//	0, 1, 1, 0,
//	1, 0, 0, 0,
//	0, 1, 1, 0,
//	0, 0, 0, 1),
//	glv_dmat4(
//	0, 1, 0, 0,
//	1, 0, 1, 0,
//	1, 0, 1, 0,
//	0, 0, 0, 1)
//};


	gl_uniform_buffer ub(
		"Matrices", 
		gl_uniform_buffer_enum::layout::shared,
		gl_uniform_buffer_enum::matrix_layout::row_major,
		gl_uniform_buffer_enum::reference_style::global,
		{
			gl_uniform_buffer_enum::reference_shader::vertex_shader,
			gl_uniform_buffer_enum::reference_shader::fragment_shader
		},
		{
			gl_uniform_buffer_item("vec3", "color"),
			gl_uniform_buffer_item("vec4", "normal"),
			gl_uniform_buffer_item("vec4", "position")
		},
		{
			gl_uniform_buffer_item_array("vec2", "tails")
		});

	

	// uniforms
	auto camera_position = create_uniform("camera_position", glv_f32vec3(1.0f, 0.0f, 0.0f));
	auto spe_color = create_uniform("spe_color", glv_f32vec4(1.0f, 1.0f, 0.5f, 1.0f));

	// textures
	auto container2 = std::make_shared<gl_texture_2d>();
	gl_texture_pixels container2_pixels("assets/Textures/container2.png");
	container2->fill(container2_pixels.width, container2_pixels.height, container2_pixels.format, (const void*)container2_pixels.pixels);
	container2->set_name("container2");

	auto albedo_map = std::make_shared<gl_texture_2d>();
	gl_texture_pixels albedo_pixels("assets/Materials/Rock030_2k-JPG/Rock030_2K_Color.jpg");
	albedo_map->fill(albedo_pixels.width, albedo_pixels.height, albedo_pixels.format, (const void*)albedo_pixels.pixels);
	albedo_map->set_name("container3");



	// vertex array
	auto vaod = sptr(gl_vertex_array_descriptor);
	vaod->add_attributes(positions);
	vaod->add_attributes(uvs);
	vaod->add_attributes(tests);

	auto vao = std::make_shared<gl_vertex_array>(vaod);

	// element array
	auto ebod = std::make_shared<gl_element_array_buffer_descriptor>();
	auto ebo = std::make_shared<gl_element_array_buffer>();
	ebod->set_indices(indices);
	ebo->fill(ebod);

	// ubo
	auto u0 = create_uniform("color", glu_f32vec4(1.0f, 0.0f, 0.0f, 1.0f));
	auto u1 = create_uniform("pos", glu_f32vec3(0.0f, 1.0f, 0.0f));
	auto u2 = create_uniform("text", glu_f32vec4(0.0f, 0.0f, 1.0f, 1.0f));
	auto ubod = std::make_shared<gl_uniform_buffer_descriptor>();
	ubod->set_block_name("attack");
	ubod->add_uniform(u0);
	ubod->add_uniform(u1);
	ubod->add_uniform(u2);
	auto ubo = std::make_shared<gl_uniform_buffer>(ubod);

	// ubo1
	auto u01 = create_uniform("color1", glu_f32vec4(1.0f, 0.0f, 0.0f, 1.0f));
	auto u11 = create_uniform("pos1", glu_f32vec3(0.0f, 1.0f, 0.0f));
	auto u21 = create_uniform("text1", glu_f32vec4(0.0f, 0.0f, 1.0f, 1.0f));
	auto ubod1 = std::make_shared<gl_uniform_buffer_descriptor>();
	ubod1->set_block_name("attack1");
	ubod1->add_uniform(u01);
	ubod1->add_uniform(u11);
	ubod1->add_uniform(u21);
	auto ubo1 = std::make_shared<gl_uniform_buffer>(ubod1);

	// ssbo
	auto ssbod = std::make_shared<gl_shader_storage_buffer_descriptor>();
	ssbod->set_block_name("genda");
	ssbod->add_variables({
			create_uniform("st", glu_f32vec4(1.0f, 0.0f, 0.0f, 1.0f)),
			create_uniform("ps", glu_f32vec4(0.0f, 1.0f, 0.0f, 1.0f)),
			create_uniform("txt", glu_f32vec4(0.0f, 0.0f, 1.0f, 1.0f))
		});
	auto ssbo = std::make_shared<gl_shader_storage_buffer>(ssbod);

	// program
	auto program = std::make_shared<gl_program>();
	program->construct({
		"shaders/test.vert",
		"shaders/test.frag" });
	program->set_vertex_array(vao);
	program->set_element_array_buffer(ebo);
	
	program->add_texture(container2);
	program->add_texture(albedo_map);
	
	program->add_uniform(camera_position);
	program->add_uniform(spe_color);

	program->add_uniform_buffer(ubo);
	program->add_uniform_buffer(ubo1);
	program->add_shader_storage_buffer(ssbo);
	
	
	program->set_framebuffer();
	program->set_commands([] {
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		});

	//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_FILL GL_POINT
	//glFrontFace(GL_CW);//default 逆时针 GL_CW 顺时针

	//glEnable(GL_COLOR_BUFFER_BIT);
	//glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	//glEnable(GL_ACCUM_BUFFER_BIT);
	//glClearAccum(1.0f, 0.2f, 1.0f, 1.0f);

	// when current frag-z < 1.0, keep it
	// fragShader write its z value before working
	//glEnable(GL_DEPTH_TEST);
	//glDepthFunc(GL_LESS);
	//glDepthMask(GL_TRUE);
	//glClearDepth(1.0f);

	//glEnable(GL_STENCIL_TEST);
	//glStencilFunc(GL_ALWAYS, 1, 0xFF);
	//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
	//glStencilMask(GL_TRUE);
	//glClearStencil(0);

	int i = 300;
	float w = 0.0f;
	while (i--)
	{
		
		//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClear(GL_COLOR_BUFFER_BIT);
		
		program->render(0.0f);
		window->tick(0.0f);
		
		/*ubod->clear_uniforms();
		ubod->add_uniforms({
			create_uniform("color", glu_f32vec4(w, 0.0f, 0.0f, 1.0f)),
			create_uniform("pos", glu_f32vec3(0.0f, 0.0f, 0.0f)),
			create_uniform("text", glu_f32vec4(0.0f, 0.0f, 0.0f, 1.0f))
			});
		w += 0.001f;*/
	}
}
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
//	//glFrontFace(GL_CW);//default 逆时针 GL_CW 顺时针
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

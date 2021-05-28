
#include "graphics/program/gl_program.h"
#include "graphics/variable/gl_variable.h"
#include "graphics/buffer/customization/gl_element_array_buffer.h"
#include "graphics/vertex_array/gl_vertex_array.h"
#include "window/window.h"

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

std::vector<float> normals{
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
		0.0f,  1.0f,  0.0f,
};

std::vector<float> offset_positions{
	0.0f,  0.0f,  0.0f,
	2.0f,  5.0f, -15.0f,
	-1.5f, -2.2f, -2.5f,
	-3.8f, -2.0f, -12.3f,
	2.4f, -0.4f, -3.5f,
	-1.7f,  3.0f, -7.5f,
	1.3f, -2.0f, -2.5f,
	1.5f,  2.0f, -2.5f,
	1.5f,  0.2f, -1.5f,
	-1.3f,  1.0f, -1.5f,
};

std::vector<float> uvs{
		0.0f,  0.0f,
		1.0f,  0.0f,
		1.0f,  1.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  0.0f,

		0.0f,  0.0f,
		1.0f,  0.0f,
		1.0f,  1.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  0.0f,

		1.0f,  0.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  0.0f,
		1.0f,  0.0f,

		1.0f,  0.0f,
		1.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  1.0f,
		0.0f,  0.0f,
		1.0f,  0.0f,

		0.0f,  1.0f,
		1.0f,  1.0f,
		1.0f,  0.0f,
		1.0f,  0.0f,
		0.0f,  0.0f,
		0.0f,  1.0f,

		0.0f,  1.0f,
		1.0f,  1.0f,
		1.0f,  0.0f,
		1.0f,  0.0f,
		0.0f,  0.0f,
		0.0f,  1.0f
};

std::vector<float> positions{
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,

		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,

		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,

		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f,  0.5f,
		-0.5f, -0.5f, -0.5f,

		-0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		 0.5f,  0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f, -0.5f
};


struct _std140_matrices
{
	glm::mat4 model_matix;
	glm::mat4 view_matix;
	glm::mat4 projection_matix;
};

struct _std140_base_colors
{
	/*glm::vec3 directional_light_color;
	float _alignment0;
	glm::vec3 directional_light_color;
	float _alignment1;
	glm::vec3 directional_light_color;
	float _alignment2;*/
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

	//glm::vec3 v = d[0];

	//

	//std::cout << v.r << std::endl;
	//std::cout << v.g << std::endl;
	//std::cout << v.b << std::endl;


	auto vao = sptr(gl_vertex_array);
	auto vaod = sptr(gl_vertex_array_descriptor);

	// colors
	vaod->add_attributes<glsl_vec4>({ 
		glsl_vec4(0.0f, 0.7f, 0.9f, 0.0f),
		glsl_vec4(0.2f, 0.8f, 0.3f, 0.0f),
		glsl_vec4(0.5f, 0.5f, 0.2f, 0.0f),
		glsl_vec4(0.1f, 0.8f, 0.2f, 0.0f),
		glsl_vec4(0.2f, 0.1f, 0.9f, 0.0f),
		});

	// uvs
	vaod->add_attributes<glsl_vec2>({
		glsl_vec2(1.0f, 0.5f),
		glsl_vec2(1.0f, 0.5f),
		glsl_vec2(0.5f, 1.0f),
		glsl_vec2(0.5f, 1.0f),
		glsl_vec2(0.5f, 1.0f),
		});

	vaod->add_attributes<glsl_dvec3>({
		glsl_dvec3(0.8290L, 0.02323L, 0.02323L),
		glsl_dvec3(0.8290L, 0.02323L, 0.02323L),
		glsl_dvec3(0.8290L, 0.02323L, 0.02323L),
		glsl_dvec3(0.8290L, 0.02323L, 0.02323L),
		glsl_dvec3(0.8290L, 0.02323L, 0.02323L)
		});

	vaod->add_attributes<glsl_float>({
		0.0f,
		0.2f,
		1.3f
		});

	vaod->add_attributes<glsl_mat2x3>({
		glsl_mat2x3(0.0f),
		glsl_mat2x3(1.0f)
		});

	vao->fill(vaod);

	//std::cout << "size :" << vaod->get_data_size() << std::endl;

	std::cout << "size :" << vao->get_attribute_components_num(0) << std::endl;
	std::cout << "size :" << vao->get_attribute_components_num(1) << std::endl;
	std::cout << "size :" << vao->get_attribute_components_num(2) << std::endl;
	std::cout << "size :" << vao->get_attribute_components_num(3) << std::endl;
	std::cout << "size :" << vao->get_attribute_components_num(4) << std::endl;
	std::cout << "size :" << vao->get_attribute_components_num(5) << std::endl;	

}

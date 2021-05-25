
#include "graphics/program/gl_program.h"
#include "graphics/uniform/gl_uniform.h"
#include "graphics/buffer/customization/gl_element_array_buffer.h"
#include "graphics/vertex_array/gl_vertex_array.h"
#include "window/window.h"


int main()
{
  
	glfw_window* window = new glfw_window();
	window->load_context();

	auto vertex_array = std::make_shared<gl_vertex_array>();
	vertex_array->fill(nullptr, 1024, {});
	
	auto element_array_buffer = std::make_shared<gl_element_array_buffer>();
	

	auto uniform0 = std::make_shared<gl_uniform<glm::mat4>>("projection_matrix", glm::mat4(0.0f));
	auto uniform1 = std::make_shared<gl_uniform<glm::mat4>>("view_matrix", glm::mat4(0.0f));
	auto uniform2 = std::make_shared<gl_uniform<glm::mat4>>("model_matrix", glm::mat4(0.0f));
	auto uniform3 = std::make_shared<gl_uniform<glm::vec3>>("camera_position", glm::vec3(1.0f));

	auto program = std::make_shared<gl_program>();

	if (program)
	{
		program->set_vertex_array(vertex_array);
		program->set_element_array_buffer(element_array_buffer);
		program->add_uniforms({ uniform0, uniform1, uniform2});
		program->add_uniforms({ uniform3 });


		program->set_framebuffer();
		program->set_commands([] {
			//glDrawElementsInstancedBaseVertexBaseInstance(GL_PATCHES, Indices.size(), GL_UNSIGNED_INT, &Indices.at(0), instanceNum, 0, 0);
			});
	}


	while (true)
	{
		window->tick(1.0f);
		program->render(1.0f);
	}

}

#ifndef GL_TEST_RENDERER_H
#define GL_TEST_RENDERER_H

#include "graphics/pipeline/graphics/gl_graphics_pipeline.h"
#include "graphics/glsl/opaque_t/glsl_sampler.h"

class gl_test_renderer
{
public:
	gl_test_renderer() 
	{
		_exit = false;
	}

	void initialize()
	{
		gl_vertex_launcher_descriptor _vertex_launcher_desc;

		_vertex_launcher_desc.primitive_mode = gl_primitive_mode::TRIANGLES;
		_vertex_launcher_desc.primitive_vertices_num = 3;
		_vertex_launcher_desc.vertex_array_descriptor = {};
		_vertex_launcher_desc.elements_num = 3 * 10;

		auto _vertex_launcher = std::make_shared<gl_vertex_launcher>(_vertex_launcher_desc);
		_vertex_launcher->execute_mapped_element_slot_writer(0, _vertex_launcher->get_elements_num(), 
			[](void* mapped_elements, uint32 elements_num) {
				uint32 indices[] = {1, 2, 3, 4, 5, 6};
				std::memcpy(mapped_elements, indices, 6 * sizeof(uint32));
			});

		std::vector<glm::u8vec4> _pixels = {
			glm::u8vec4(2,2,3, 88), 
			glm::u8vec4(134,2,73, 88), 
			glm::u8vec4(134,5,83, 88),
			glm::u8vec4(12,2,63, 88),
			glm::u8vec4(12,2,64, 88)
		};

		gl_texture_rectangle* diff_rect = new gl_texture_rectangle(1, 5, gl_texture_internal_format::NOR_UI_RG8);
		diff_rect->fill(0, 0, 1, 5, gl_texture_pixel_format::RGBA, gl_texture_pixel_type::UBYTE, _pixels.data());
		
		std::vector<glm::u8vec4> _out_pixels;
		_out_pixels.resize(5);

		for (const auto& _pixel : _out_pixels)
		{
			std::cout << (uint32)_pixel.r << "," << (uint32)_pixel.g << "," << (uint32)_pixel.b << "," <<(uint32)_pixel.a << std::endl;
		}

		diff_rect->fetch(0, 0, 1, 5, gl_texture_pixel_format::RGBA, gl_texture_pixel_type::UBYTE, 20, _out_pixels.data());

		for (const auto& _pixel : _out_pixels)
		{
			std::cout << (uint32)_pixel.r << "," << (uint32)_pixel.g << "," << (uint32)_pixel.b << "," << (uint32)_pixel.a << std::endl;
		}

		gl_graphics_pipeline_descriptor _desc;
		_desc.name = "mesh_pipeline";
		_desc.owner_renderer_dir = "/";
		_desc.vertex_launcher;
		_desc.state;
		_desc.glsl_program;
		_desc.framebuffer;

		_mesh_pipeline = std::make_unique<gl_graphics_pipeline>(_desc);

		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //GL_FILL GL_POINT
		//glFrontFace(GL_CW);//default GL_CW

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

	}

	void render(float delta_time)
	{
		if (!_mesh_pipeline) return;

		glClear(GL_COLOR_BUFFER_BIT);

		_mesh_pipeline->enable();

		_mesh_pipeline->draw_arrays(0, 1024);

		_mesh_pipeline->disable();
	}

	bool should_exit()
	{
		return _exit;
	}

	void set_exit(bool exit)
	{
		_exit = exit;
	}

private:

	std::unique_ptr<gl_graphics_pipeline> _mesh_pipeline;

	bool _exit;
};

#endif
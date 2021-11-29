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

		std::vector<glm::vec4> _pixels = {
			glm::vec4(0.232f, 0.15f, 0.23f, 0.1223f), 
			glm::vec4(0.223f, 0.15f, 0.23f, 0.343f), 
			glm::vec4(0.98f, 0.15f, 0.23f, 0.209f), 
			glm::vec4(0.71f, 0.15f, 0.23f, 0.25f)
		};

		gl_texture_2d* diffuse_texture = new gl_texture_2d(2, gl_texture_internal_format::F_RGBA32, 2, 2);
		diffuse_texture->fill(0, 0, 0, 2, 2, gl_texture_pixel_format::RGBA, gl_texture_pixel_type::FLOAT, _pixels.data());
		diffuse_texture->build_mipmaps();

		

		int32 _mipmap_index = 1;
		std::cout << "mipmap : " << _mipmap_index << std::endl;
		std::cout << "width : " << diffuse_texture->get_width(_mipmap_index) << " height : " << diffuse_texture->get_height(_mipmap_index) << " depth : " << diffuse_texture->get_depth(_mipmap_index) << std::endl;

		std::vector<glm::vec4> _out_pixels;
		_out_pixels.resize(4);


		for (const auto& _pixel : _out_pixels)
		{
			std::cout << _pixel.r << "," << _pixel.g << "," << _pixel.b << "," << _pixel.a << std::endl;
		}

		gl_texture_2d_multisample* diffuse_texture_ms = new gl_texture_2d_multisample(1, gl_texture_internal_format::F_RGBA32, 2, 2, true);
		diffuse_texture_ms->fill(0, 0, 2, 2, gl_texture_pixel_format::RGBA, gl_texture_pixel_type::FLOAT, _pixels.data());

		glsl_sampler2D* diffuse_map = new glsl_sampler2D(0, "diffuse_map");
		diffuse_map->associate_texture_2d(diffuse_texture);
		auto atx = diffuse_map->get_texture_2d();
		//atx->reallocate(2, gl_texture_internal_format::F_RGBA32, 2, 2);
		//atx->fetch(1, 0, 0, 1, 1, gl_texture_pixel_format::RGBA, gl_texture_pixel_type::FLOAT, _out_pixels.size() * sizeof(glm::vec4), _out_pixels.data());

		for (const auto& _pixel : _out_pixels)
		{
			std::cout << _pixel.r << "," << _pixel.g << "," << _pixel.b << "," << _pixel.a << std::endl;
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
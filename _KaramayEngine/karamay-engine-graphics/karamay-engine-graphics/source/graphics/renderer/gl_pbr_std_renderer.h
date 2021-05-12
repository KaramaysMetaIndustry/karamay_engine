#pragma once
#include "gl_renderer.h"
#include "graphics/commands/gl_commands.h"
#include "graphics/mesh/gl_mesh.h"

#define ctt(CLASSNAME)\
std::make_shared<CLASSNAME>()

#define add_pip(PIPName)\
_pipelines_map.emplace("pipeline0", std::make_shared<gl_pipeline_base>())\

#define find_pip(PIPName)\
_pipelines_map.find(PIPName)->second


#define add_fb(FB_NAME)\
_framebuffers_map.emplace(FB_NAME, std::make_shared<gl_framebuffer>())\

#define find_fb(FB_NAME)\
_framebuffers_map.find(FB_NAME)->second\




class gl_pbr_std_renderer : public gl_renderer
{
private:

	std::shared_ptr< gl_mesh> _mesh;

	std::float_t _view_field;
	std::float_t _view_distance;
	std::float_t _width, height;

	glm::mat4 get_projection_matrix()
	{
		return glm::perspective(glm::radians(_view_field), (float)_width / (float)-height, 0.1f, _view_distance);
	}

public:
	
	virtual void construct() override
	{
		{
			add_fb("stage0");
			add_fb("stage1");
			add_fb("Gb");
		}


		// pipeline 0
		{
			add_pip("PIP0");
			auto pip0 = find_pip("PIP0");
			if (pip0)
			{
				pip0->construct({ "","","","" }); // load shaders, compile and link
				pip0->set_framebuffer(find_fb("stage0"));
				pip0->set_vertex_array(ctt(gl_vertex_array));
				pip0->set_element_array_buffer(ctt(gl_buffer));
				pip0->set_uniform_buffers({ ctt(gl_buffer), ctt(gl_buffer) });
			}
		}
		
		// pipeline 1
		{
			auto vertex = ctt(gl_vertex_array);
			vertex->associate_array_buffer(find_fb("stage0").get);




			add_pip("PIP1");
			auto pip1 = find_pip("PIP1");
			if (pip1)
			{
				pip1->construct({});
				pip1->set_framebuffer();
				pip1->set_vertex_array()
			}
		}
		
	}


	virtual void initialize() override
	{
		
	}

	virtual void render(std::float_t delta_time) override
	{
		for (auto pair : _pipelines_map)
		{
			if (auto pipeline = pair.second)
			{
				pipeline->install();
				pipeline->enable();

				gl_commands::draw::draw_arrays(gl_commands::primitive_mode::LINE_STRIP_ADJACENCY, 0, 3);

				pipeline->disable();
			}
		}

	}








};


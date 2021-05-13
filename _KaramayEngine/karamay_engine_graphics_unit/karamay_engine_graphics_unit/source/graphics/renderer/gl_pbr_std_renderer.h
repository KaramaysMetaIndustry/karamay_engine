#pragma once
#include "gl_renderer.h"
#include "graphics/commands/gl_commands.h"
#include "graphics/mesh/gl_mesh.h"
#include "graphics/pipeline/gl_pipeline_base.h"

#define ctt(CLASSNAME)\
std::make_shared<CLASSNAME>()

#define add_pip(PIPName)\
_pipelines_map.emplace("pipeline0", std::make_shared<gl_pipeline_base>()).first->second\

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


		{
			if (auto pip0 = add_pip("pip_prb_one"))
			{
				pip0->construct({ "PBRMesh.vert","PBRMesh.tese","PBRMesh.tesc","PBRMesh.geom", "PBRMesh.frag" }); // load shaders, compile and link
				pip0->set_framebuffer();
				pip0->set_vertex_array(ctt(gl_vertex_array));
				pip0->set_uniform_buffer(ctt(gl_uniform_buffer));
				pip0->set_shader_storage_buffers(ctt(gl_shader_storage_buffer));
				pip0->set_atomic_count_buffer(ctt(gl_atomic_count_buffer));
				pip0->set_transform_feedback_varyings({"",""});
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


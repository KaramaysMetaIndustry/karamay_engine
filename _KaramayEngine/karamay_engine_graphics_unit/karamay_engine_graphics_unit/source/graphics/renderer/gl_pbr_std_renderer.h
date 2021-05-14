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
	
	gl_pipeline_base& find_pipeline(const std::string name)
	{
		return *_pipelines_map.find(name)->second;
	}

#define graphics_pipeline(NAME)\
find_pipeline(NAME)\

	virtual void construct() override
	{
		
		auto vao = std::make_shared<gl_vertex_array>();
		auto ebo = std::make_shared<gl_element_array_buffer>();
		auto ubo0 = std::make_shared<gl_uniform_buffer>();
		auto ubo1 = std::make_shared<gl_uniform_buffer>();
		auto ubo2 = std::make_shared<gl_uniform_buffer>();
		auto sso0 = std::make_shared<gl_shader_storage_buffer>();
		auto sso1 = std::make_shared<gl_shader_storage_buffer>();
		auto aco = std::make_shared<gl_atomic_count_buffer>();
		auto transfo = std::make_shared<gl_transform_feedback>();

		// single pipeline render pass

		graphics_pipeline("pbr_mesh_pip")
		.construct({ "pbr_mesh.vert", "pbr_mesh.tesc", "pbr_mesh.tese", "pbr_mesh.geom", "pbr_mesh.frag" })
		.add_vertex_kit(vao)
		.add_transform_feedback(transfo, { "tf_position, tf_color, tf_vu" })
		.add_uniform_buffers({ ubo0, ubo1, ubo2 })
		.add_shader_storage_buffers({ sso0, sso1 })
		.add_atomic_count_buffers({ aco })
		.add_texture_2ds({})
		.add_framebuffer();

		
		// multi pipeline render pass
		graphics_pipeline("deferred_pbr_mesh_vert_pip")
		.construct({ "pbr_mesh.vert", "pbr_mesh.tesc", "pbr_mesh.tese", "pbr_mesh.geom", "pbr_mesh.frag" })
		.add_vertex_kit(vao, ebo)
		.add_transform_feedback(transfo, { "tf_position, tf_color, tf_vu" })
		.add_uniform_buffers({ ubo0, ubo1, ubo2 })
		.add_shader_storage_buffers({ sso0, sso1 })
		.add_atomic_count_buffers({ aco })
		.add_texture_2ds({})
		.add_framebuffer();

		graphics_pipeline("deferred_pbr_mesh_lighting_pip")
		.construct({ "pbr_mesh.vert", "pbr_mesh.frag" })
		.add_vertex_kit()
		.add_transform_feedback(transfo, { "tf_position, tf_color, tf_vu" })
		.add_uniform_buffers({ ubo0, ubo1, ubo2 })
		.add_shader_storage_buffers({ sso0, sso1 })
		.add_atomic_count_buffers({ aco })
		.add_texture_2ds({})
		.add_framebuffer();
	}

	virtual void render(std::float_t delta_time) override
	{
		for (auto pair : _pipelines_map)
		{
			if (auto pipeline = pair.second)
			{
				pipeline->enable();
				gl_commands::draw::draw_arrays(gl_commands::primitive_mode::LINE_STRIP_ADJACENCY, 0, 3);
				pipeline->disable();
			}
		}

	}








};


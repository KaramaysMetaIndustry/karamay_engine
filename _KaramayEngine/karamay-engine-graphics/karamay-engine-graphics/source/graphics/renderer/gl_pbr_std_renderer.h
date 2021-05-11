#pragma once
#include "gl_renderer.h"
#include "graphics/commands/gl_commands.h"
#include "graphics/mesh/gl_mesh.h"

#define ADD_FB(FB_NAME)\
_framebuffers_map.emplace(FB_NAME, std::make_shared<gl_framebuffer>())\

#define FIND_FB(FB_NAME)\
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
			_final_framebuffer = std::make_shared<gl_default_framebuffer>();
			ADD_FB("FB0");
			ADD_FB("FB1");
			ADD_FB("FB2");

			auto fb0 = FIND_FB("FB0");
			if (fb0) {
				//fb0->attach_color_buffer_1d(0, );
			}





			
		}

		
		{
			_programs_map.emplace("program0", std::shared_ptr<gl_program>());
			auto program0 = _programs_map.find("program0")->second;
			program0->construct({
				"/shaders/PBRMesh.vert",
				"/shaders/PBRMesh.tesc",
				"/shaders/PBRMesh.tese",
				"/shaders/PBRMesh.geom",
				"/shaders/PBRMesh.frag"
				});
		}
	}


	virtual void initialize() override
	{
		{
			auto program0 = _programs_map.find("geom_handler")->second;
			if (program0)
			{
		

				
			}

		}
	}

	virtual void render(std::float_t delta_time) override
	{
		// program 0 
		{
			auto program0 = _programs_map.find("program0")->second;

			if (program0)
			{
				program0->bind_framebuffer(nullptr); // bind default framebuffer
				program0->bind_vertex_array(_mesh->vertex_array); // bind vertex array

				program0->bind_texture_2d(0, "PBRMaterial.albedo_map", std::make_shared<gl_texture_2d>());
				program0->bind_texture_2d(1, "PBRMaterial.normal_map", std::make_shared<gl_texture_2d>());
				program0->bind_texture_2d(2, "PBRMaterial.metalness_map", std::make_shared<gl_texture_2d>());
				program0->bind_texture_2d(3, "PBRMaterial.roughness_map", std::make_shared<gl_texture_2d>());
				program0->bind_texture_2d(4, "PBRMaterial.displacement_map", std::make_shared<gl_texture_2d>());
				program0->bind_texture_2d(5, "PBRMaterial.ambient_occlusion_map", std::make_shared<gl_texture_2d>());

				for (const auto& pair : _mesh->material->texture_2ds_map)
				{
					program0->bind_texture_2d(0, pair.first, pair.second);
				}


				// set uniforms
				program0->update_uniform_3f("camera_position", glm::vec3());
				program0->update_uniform_matrix_4x4f("model_matrix", glm::mat4());
				program0->update_uniform_matrix_4x4f("view_matrix", glm::mat4());
				program0->update_uniform_matrix_4x4f("projection_matrix", get_projection_matrix());

				program0->enable();
				gl_commands::draw::draw_elements_instanced_base_instance();
				program0->disable();
			}
		}


		// program 1
		{
			auto program_ray = _programs_map.find("program_ray")->second;
			if (program_ray)
			{
				program_ray->render(1.0f);
			}
		}

	}








};


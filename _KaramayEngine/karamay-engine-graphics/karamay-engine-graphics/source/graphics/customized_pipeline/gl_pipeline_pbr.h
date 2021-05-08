#pragma once
#include "graphics/program/gl_program.h"
#include "graphics/program_pipeline/gl_program_pipeline.h"

class gl_pipeline_pbr : public gl_program_pipeline
{
public:

	virtual void construct() override
	{
		auto program = std::make_shared<gl_program>();
		if (program) {
			_program = program;
			_program->construct({ "PBRMesh.vert", "PBRMesh.tesc", "PBRMesh.tese", "PBRMesh.geom", "PBRMesh.frag" });
		}

	}

	virtual void render(std::float_t delta_time) override
	{
		if (_program) {

			_program->set_vertex_array(std::make_shared<gl_vertex_array>());
			_program->set_element_array_buffer(std::make_shared<gl_buffer>());

			_program->set_uniform_matrix_4x4f("model_matrix", glm::fmat4(0.0f));
			_program->set_uniform_matrix_4x4f("view_matrix", glm::fmat4(0.0f));
			_program->set_uniform_matrix_4x4f("projection_matrix", glm::fmat4(0.0f));
			_program->set_uniform_3f("base_color", { 0.0f, 0.2f, 0.5f });
			_program->set_uniform_1d("scale", glm::dvec1(2.0));

			_program->set_texture_2d(0, "albedo_map", std::make_shared<gl_texture_2d>());
			_program->set_texture_2d(1, "metallic_map", std::make_shared<gl_texture_2d>());
			_program->set_texture_2d(2, "roughness_map", std::make_shared<gl_texture_2d>());
			_program->set_texture_2d(3, "normal_map", std::make_shared<gl_texture_2d>());
			_program->set_texture_2d(4, "displacement_map", std::make_shared<gl_texture_2d>());

			_program->set_uniform_buffer(0, "material", std::make_shared<gl_buffer>());
			_program->set_uniform_buffer(1, "light", std::make_shared<gl_buffer>());

			_program->set_shader_storage_buffer(0, "cached_light_volume", std::make_shared<gl_buffer>());

			_program->set_atomic_count_buffer(0, std::make_shared<gl_buffer>());
			

			_program->enable();
			// call draw commands


			// end draw commands
			_program->disable();
		}
		
	}


private:
	std::shared_ptr<gl_program> _program;
};


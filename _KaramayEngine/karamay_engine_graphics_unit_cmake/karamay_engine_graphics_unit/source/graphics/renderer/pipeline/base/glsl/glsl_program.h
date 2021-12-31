#ifndef GLSL_PROGRAM_H
#define GLSL_PROGRAM_H

#include "glsl.h"
#include "glsl_builder.h"
#include "glsl_shader.h"
#include "graphics/renderer/pipeline/base/resource/program/gl_program.h"

class glsl_program 
{
public:
	glsl_program() = default;

	glsl_program(const glsl_program&) = delete;
	glsl_program& operator=(const glsl_program&) = delete;

	~glsl_program() = default;

public:

	bool generate_templates(const std::string& dir)
	{
		for (auto _shader : _shaders)
		{
			_shader->generate_template(dir);
		}

		return false;
	}

	bool load() { return false; }

public:

	glsl_uniform_block* uniform_block(const std::string& block_name)
	{
		auto _it = _uniform_blocks.find(block_name);
		if (_it != _uniform_blocks.cend()) return _it->second;
		return nullptr;
	}
	glsl_shader_storage_block* shader_storage_block(const std::string& block_name)
	{
		auto _it = _shader_storage_blocks.find(block_name);
		if (_it != _shader_storage_blocks.cend()) return _it->second;
		return nullptr;
	}
	glsl_atomic_counter* atomic_uint(const std::string& block_name)
	{
		auto _it = _atomic_counters.find(block_name);
		if (_it != _atomic_counters.cend()) return _it->second;
		return nullptr;
	}

protected:

	template<typename T>
	T* _create_shader()
	{
		return new T();
	}

	template<typename T>
	T* _create_uniform_block()
	{
		return new T();
	}

	template<typename T>
	T* _create_shader_storage_block()
	{
		return new T();
	}

private:

	std::vector<glsl_shader*> _shaders;

	std::unordered_map<std::string, glsl_uniform_block*> _uniform_blocks;
	std::unordered_map<std::string, glsl_shader_storage_block*> _shader_storage_blocks;
	std::unordered_map<std::string, glsl_atomic_counter*> _atomic_counters;

};

class glsl_graphics_pipeline_program : public glsl_program 
{
public:
	glsl_graphics_pipeline_program() = default;

	glsl_graphics_pipeline_program(const glsl_graphics_pipeline_program&) = delete;
	glsl_graphics_pipeline_program& operator=(const glsl_graphics_pipeline_program&) = delete;

	~glsl_graphics_pipeline_program() = default;

public:

	void load()
	{
		// generate template, if has no file, generate
		
		// generate template, if has file and but 'force' is active generate file

		// if has file and forces is not active, load file and validate with template
		std::string renderer_path = "C:/PrivateRepos/Karamays/_KaramayEngine/karamay_engine_graphics_unit_cmake/karamay_engine_graphics_unit/shaders/Mesh/PBRMesh";
		std::vector<gl_shader*> _shaders;
		if (_vertex_shader) {
			_vertex_shader->load(renderer_path + "/PBRMesh.vert");
			_shaders.push_back(_vertex_shader->get_shader());
		}
		if (_tesc_shader && _tese_shader)
		{
			if (_tesc_shader->load(renderer_path + "/PBRMesh.tesc") && _tese_shader->load(renderer_path + "/PBRMesh.tese"))
			{
			}
		}
		if (_geometry_shader)
		{
			_geometry_shader->load(renderer_path + "/PBRMesh.geom");
			_shaders.push_back(_geometry_shader->get_shader());
		}
		if (_fragment_shader) 
		{
			_fragment_shader->load(renderer_path + "/PBRMesh.frag");
			_shaders.push_back(_fragment_shader->get_shader());
		}

		_program = new gl_program();
		
		if (_program->load(_shaders))
			std::cout << "program load successful" << std::endl;
		else
			std::cerr << "program load failed" << std::endl;
	}

	void enable() {}

	void disable() {}

private:
	gl_program* _program;
	glsl_vertex_shader* _vertex_shader;
	glsl_tessellation_control_shader* _tesc_shader;
	glsl_tessellation_evaluation_shader* _tese_shader;
	glsl_geometry_shader* _geometry_shader;
	glsl_fragment_shader* _fragment_shader;

};

class glsl_compute_pipeline_program : public glsl_program
{
public:
	glsl_compute_pipeline_program(glsl_compute_shader* compute_shader) :
		_program(nullptr),
		_cs(compute_shader)
	{}

	glsl_compute_pipeline_program(const glsl_compute_pipeline_program&) = delete;
	glsl_compute_pipeline_program& operator=(const glsl_compute_pipeline_program&) = delete;

	~glsl_compute_pipeline_program()
	{
		delete _program;
		delete _cs;
	}

private:
	gl_program* _program;
	glsl_compute_shader* _cs;

public:
	
	void load()
	{

	}

	void enable()
	{

	}

	void disable()
	{

	}

};

#endif
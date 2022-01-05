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

	virtual bool load(const std::string& pipeline_dir) = 0;
	virtual bool generate_template(const std::string& pipeline_dir) = 0;

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

	void enable() { if (_program) _program->enable(); }

	void disable() { if (_program) _program->disable(); }

protected:

	std::vector<glsl_shader*> _shaders;
	std::unordered_map<std::string, glsl_uniform_block*> _uniform_blocks;
	std::unordered_map<std::string, glsl_shader_storage_block*> _shader_storage_blocks;
	std::unordered_map<std::string, glsl_atomic_counter*> _atomic_counters;

	gl_program* _program;

protected:

	template<typename GLSL_SHADER>
	GLSL_SHADER* _create_shader() noexcept
	{
		static_assert(std::is_base_of_v<glsl_shader, GLSL_SHADER>, "you must specify a glsl shader type.");
		GLSL_SHADER* _shader = new GLSL_SHADER();
		_shaders.push_back(_shader);
		return _shader;
	}

	template<typename GLSL_UNIFORM_BLOCK>
	GLSL_UNIFORM_BLOCK* _create_uniform_block() noexcept
	{
		static_assert(std::is_base_of_v<glsl_uniform_block, GLSL_UNIFORM_BLOCK>, "you must specify a glsl uniform block type.");
		GLSL_UNIFORM_BLOCK* _uniform_block = new GLSL_UNIFORM_BLOCK();
		_uniform_blocks.emplace(_uniform_block->block_name(), _uniform_block);
		return _uniform_block;
	}

	template<typename GLSL_SHADER_STORAGE_BLOCK>
	GLSL_SHADER_STORAGE_BLOCK* _create_shader_storage_block() noexcept
	{
		static_assert(std::is_base_of_v<glsl_shader_storage_block, GLSL_SHADER_STORAGE_BLOCK>, "you must specify a glsl shader storage block type.");
		GLSL_SHADER_STORAGE_BLOCK* _shader_storage_block = new GLSL_SHADER_STORAGE_BLOCK();
		_shader_storage_blocks.emplace(_shader_storage_block->block_name(), _shader_storage_block);
		return _shader_storage_block;
	}

	template<typename GLSL_ATOMIC_COUNTER>
	GLSL_ATOMIC_COUNTER* _create_atomic_counter() noexcept
	{
		static_assert(std::is_base_of_v<glsl_atomic_counter, GLSL_ATOMIC_COUNTER>, "you must specify a glsl atomic counter type.");
		GLSL_ATOMIC_COUNTER* _atomic_counter = new GLSL_ATOMIC_COUNTER();
		return _atomic_counter;
	}

};

class glsl_graphics_pipeline_program : public glsl_program 
{
public:
	glsl_graphics_pipeline_program() = default;

	glsl_graphics_pipeline_program(const glsl_graphics_pipeline_program&) = delete;
	glsl_graphics_pipeline_program& operator=(const glsl_graphics_pipeline_program&) = delete;

	~glsl_graphics_pipeline_program() = default;

public:

	bool load(const std::string& pipeline_dir) override
	{
		// generate template, if has no file, generate
		// generate template, if has file and but 'force' is active generate file

		// if has file and forces is not active, load file and validate with template
		std::vector<gl_shader*> _real_shaders;
		for (auto _shader : _shaders)
		{
			_shader->load(pipeline_dir);
			_real_shaders.push_back(_shader->get_shader());
		}


		_program = new gl_program();
		if (_program->load(_real_shaders))
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	bool generate_template(const std::string& pipeline_dir) override
	{
		return false;
	}
};

class glsl_compute_pipeline_program : public glsl_program
{
public:
	glsl_compute_pipeline_program() = default;

	glsl_compute_pipeline_program(const glsl_compute_pipeline_program&) = delete;
	glsl_compute_pipeline_program& operator=(const glsl_compute_pipeline_program&) = delete;

	~glsl_compute_pipeline_program() = default;

public:
	
	bool load(const std::string& pipeline_dir) override
	{
		if (_shaders.size() != 1) return false;

		return true;
	}

	bool generate_template(const std::string& pipeline_dir) override
	{
		return false;
	}

};

#define def_graphicsPipelineProgram(name)\
class glsl_##name##_pipeline_program : public glsl_graphics_pipeline_program\
{\
public:\

#define decl_graphicsPipelineProgram(name)\
glsl_##name##_pipeline_program* _##name##_pipeline_program = new glsl_##name##_pipeline_program();


#define def_computePipelineProgram(name)\
class glsl_##name##_pipeline_program : public glsl_compute_pipeline_program\
{\
public:\

#define decl_computePipelineProgram(name)\
class glsl_##name##_pipeline_program* _##name##_pipeline_program = new glsl_##name##_pipeline_program();

#endif
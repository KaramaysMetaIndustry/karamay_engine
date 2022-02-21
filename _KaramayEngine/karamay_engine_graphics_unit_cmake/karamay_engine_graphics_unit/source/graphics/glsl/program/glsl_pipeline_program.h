#ifndef GLSL_PROGRAM_H
#define GLSL_PROGRAM_H
#include "graphics/glsl/glsl.h"
#include "graphics/glsl/glsl_builder.h"
#include "graphics/resource/program/gl_program.h"

class glsl_pipeline_program
{
public:
	glsl_pipeline_program() = default;

	glsl_pipeline_program(const glsl_pipeline_program&) = delete;
	glsl_pipeline_program& operator=(const glsl_pipeline_program&) = delete;

	~glsl_pipeline_program() = default;

public:
	
	virtual bool load(const std::string& pipeline_dir) = 0;

	virtual bool generate_template(const std::string& pipeline_dir) = 0;

protected:

	std::vector<glsl_shader*> _shaders;

	std::unordered_map<std::string, glsl_uniform_block*> _uniform_blocks;
	
	std::unordered_map<std::string, glsl_shader_storage_block*> _shader_storage_blocks;
	
	std::unordered_map<std::string, glsl_atomic_counter*> _atomic_counters;

public:

	glsl_uniform_block* invoke_uniform_block(const std::string& block_name)
	{
		auto _it = _uniform_blocks.find(block_name);
		if (_it != _uniform_blocks.cend()) return _it->second;
		return nullptr;
	}
	
	glsl_shader_storage_block* invoke_shader_storage_block(const std::string& block_name)
	{
		auto _it = _shader_storage_blocks.find(block_name);
		if (_it != _shader_storage_blocks.cend()) return _it->second;
		return nullptr;
	}

	glsl_atomic_counter* invoke_atomic_uint(const std::string& block_name)
	{
		auto _it = _atomic_counters.find(block_name);
		if (_it != _atomic_counters.cend()) return _it->second;
		return nullptr;
	}

public:

	gl_program* _program;

	void enable() 
	{ 
		if (_program) _program->enable(); 
	}

	void disable() 
	{ 
		if (_program)
		{
			_program->disable();
		}
	}

	uint32 get_program_handle() const { return _program->get_handle(); }

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


#endif
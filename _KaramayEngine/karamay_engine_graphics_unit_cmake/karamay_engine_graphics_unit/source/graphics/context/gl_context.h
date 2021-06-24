#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer.h"

class gl_context
{

private:

	std::unordered_map<std::string, std::shared_ptr<gl_buffer>> _buffers_pool;

	std::shared_ptr<gl_buffer> _uniform_buffers_pool;

public:

	std::shared_ptr<gl_buffer> get_uniform_buffers_pool()
	{
		return _uniform_buffers_pool;
	}


	static std::vector<std::uint32_t> fetch_uniform_buffer_bindings(std::uint32_t num)
	{

	}

	static std::vector<std::uint32_t> fetch_shader_storage_buffer_bindings()
	{
	}


	static std::vector<std::uint32_t> fetch_atomic_count_buffer_bindings()
	{

	}

	auto fetch(const std::string& public_buffer_name)
	{
		return _buffers_pool.find(public_buffer_name)->second;
	}


};


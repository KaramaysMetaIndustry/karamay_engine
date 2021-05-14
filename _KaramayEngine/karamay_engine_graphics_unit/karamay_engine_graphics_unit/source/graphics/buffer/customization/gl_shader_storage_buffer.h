#pragma once
#include "graphics/buffer/gl_buffer.h"

struct gl_shader_storage_binding_info
{
	std::string block_name;

	std::shared_ptr<gl_buffer> buffer;

	std::size_t offset;

	std::size_t size;
};


class gl_shader_storage_buffer
{

public:

	auto get_binding_info()
	{
		return gl_shader_storage_binding_info();
	}

};


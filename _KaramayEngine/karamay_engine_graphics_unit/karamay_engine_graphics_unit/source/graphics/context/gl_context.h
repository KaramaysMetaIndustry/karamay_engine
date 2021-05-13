#pragma once
#include "graphics/glo/gl_object.h"
#include "graphics/buffer/gl_buffer.h"

class gl_context
{

private:

	std::unordered_map<std::string, std::shared_ptr<gl_buffer>> _buffers_pool;


public:
	auto fetch(const std::string& public_buffer_name)
	{
		return _buffers_pool.find(public_buffer_name)->second;
	}




};


#pragma once

struct gl_atomic_count_buffer_binding_info
{
	std::string block_name;

	std::shared_ptr<gl_buffer> buffer;

	std::size_t offset;

	std::size_t size;
};

class gl_atomic_count_buffer
{
public:
	auto get_binding_info()
	{
		return gl_atomic_count_buffer_binding_info();
	}
};


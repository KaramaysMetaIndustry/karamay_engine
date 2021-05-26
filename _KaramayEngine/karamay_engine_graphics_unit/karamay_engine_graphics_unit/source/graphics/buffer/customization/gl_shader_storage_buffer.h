#pragma once
#include "graphics/buffer/gl_buffer.h"

namespace gl_shader_storage_buffer_enum
{
	enum class layout
	{
		packed,
		shared,
		std140,
		std430
	};
}

struct gl_shader_storage_buffer_descriptor
{
	std::string block_name;

	const void* data;

	std::size_t size;
};


class gl_shader_storage_buffer
{
public:

	gl_shader_storage_buffer();

	virtual ~gl_shader_storage_buffer();

private:

	std::shared_ptr<gl_shader_storage_buffer_descriptor> _descriptor;

	std::shared_ptr<gl_buffer> _buffer;

	std::uint32_t _binding;

public:

	void update(std::float_t delta_time);

	void bind(std::uint32_t binding)
	{
		glBindBufferRange(GL_SHADER_STORAGE_BUFFER, binding, _buffer->get_handle(), 0, _descriptor->size);
		_binding = binding;
	}

	void unbind()
	{

	}

private:

	void _fill() {}

	void _generate_template_code()
	{
		std::regex pattern("layout (binding = 0, std430) buffer my_vertices {}");
	}

};


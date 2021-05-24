#pragma once
#include "graphics/buffer/gl_buffer.h"

struct gl_shader_storage_buffer_binding_info
{
	std::string block_name;

	std::shared_ptr<gl_buffer> buffer;

	std::size_t offset;

	std::size_t size;
};

namespace gl_shader_storage_buffer_enum
{
	enum class layout
	{

	};
}


/**
 *
 * packed
 * shared
 * std140
 * std430
 *
 */

class gl_shader_storage_buffer
{

public:

	gl_shader_storage_buffer();

	virtual ~gl_shader_storage_buffer();


private:

	std::string _block_name;

	std::shared_ptr<gl_buffer> _referred_buffer;

	std::uint32_t _offset, _size;

	std::uint32_t _index;

public:

	void fill()
	{

	}

	void bind(std::uint32_t index)
	{
		glBindBufferRange(GL_SHADER_STORAGE_BUFFER, index, _referred_buffer->get_handle(), _offset, _size);
		_index = index;
	}

	void unbind()
	{

	}


	const std::string& get_block_name()
	{
		return _block_name;
	}

private:

	void _generate_template_code()
	{
		std::regex pattern("layout (binding = 0, std430) buffer my_vertices {}");
	}

};


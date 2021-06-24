#include "gl_shader_storage_buffer.h"
#include "graphics/program/gl_program.h"


gl_shader_storage_buffer_descriptor::gl_shader_storage_buffer_descriptor() :
	_memory_layout(gl_shader_storage_buffer_enum::layout::std430),
	_matrix_memory_layout(gl_shader_storage_buffer_enum::matrix_layout::row_major),
	_block_name(),
	_items(),
	_is_dirty(true)
{
	_items.reserve(5);
}

std::shared_ptr<gl_shader_storage_buffer_descriptor> gl_shader_storage_buffer::get_descriptor()
{
	return _descriptor;
}

void gl_shader_storage_buffer::bind(std::uint32_t binding)
{
	if (_descriptor)
	{
		if (_descriptor->is_dirty())
		{
			if (_descriptor->get_memory_layout() == gl_shader_storage_buffer_enum::layout::std140)
			{
				_fill_std140();
			}
			else
			{
				_fill_std430();
			}
			_descriptor->set_dirty(false);
		}
	}

	glBindBufferRange(GL_SHADER_STORAGE_BUFFER, binding, _buffer->get_handle(), 0, _buffer->get_size());
	//_binding = binding;
}

void gl_shader_storage_buffer_descriptor::add_variable(const std::shared_ptr<gl_variable>& variable)
{
	if (variable)
	{
		_items.push_back(variable);
		_is_dirty = true;
	}
}

gl_shader_storage_buffer::~gl_shader_storage_buffer()
{

}

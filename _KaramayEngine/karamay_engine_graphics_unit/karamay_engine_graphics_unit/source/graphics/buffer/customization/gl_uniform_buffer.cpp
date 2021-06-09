#include "gl_uniform_buffer.h"
#include "graphics/program/gl_program.h"



gl_uniform_buffer::gl_uniform_buffer(const std::shared_ptr<gl_uniform_buffer_descriptor>& descriptor) :
	_descriptor(descriptor)
{

}

void gl_uniform_buffer::bind(std::int32_t binding, gl_program& program)
{
	if (_descriptor)
	{
		// if descriptor is dirty, update the buffer
		if (_descriptor->is_dirty())
		{
			if (_descriptor->get_memory_layout() == gl_uniform_buffer_enum::layout::shared ||
				_descriptor->get_memory_layout() == gl_uniform_buffer_enum::layout::packed)
			{
				_fill_shared_packed(program);
			}
			else
			{
				_fill_std140();
			}
			_descriptor->set_dirty(false);
		}
		glBindBufferRange(GL_UNIFORM_BUFFER, binding, _buffer->get_handle(), 0, _buffer->get_size());
	}
}

void gl_uniform_buffer::unbind()
{
	glBindBufferRange(GL_UNIFORM_BUFFER, _binding, 0, 0, 0);
	_binding = 0;
}

void gl_uniform_buffer::_fill_shared_packed(const gl_program& program)
{
	if (_descriptor)
	{
		const std::size_t _block_size 
			= program.get_uniform_buffer_block_size(_descriptor->get_block_name());

		_buffer = std::make_shared<gl_buffer>();
		_buffer->allocate(_block_size);

		std::size_t _offset = 0;
		for (const auto& _item : _descriptor->get_items())
		{
			if (_item)
			{
				_offset = program.get_uniform_buffer_item_offset(_item->get_name());
				_buffer->fill(_offset, _item->get_value().size(), _item->get_value().data());
			}
		}

	}
}

void gl_uniform_buffer::_fill_std140()
{
}

gl_uniform_buffer::~gl_uniform_buffer()
{
}

gl_uniform_buffer_descriptor::gl_uniform_buffer_descriptor() :
	_memory_layout(gl_uniform_buffer_enum::layout::shared),
	_memory_matrix_layout(gl_uniform_buffer_enum::matrix_layout::row_major),
	_block_name(),
	_is_dirty(true)
{

}

void gl_uniform_buffer_descriptor::add_uniform(const std::shared_ptr<gl_variable>& item)
{
	if (item)
	{
		_items.push_back(item);
		_is_dirty = true;
	}
}

void gl_uniform_buffer_descriptor::clear_uniforms()
{
	_items.clear();
}

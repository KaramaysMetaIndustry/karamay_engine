#include "gl_uniform_buffer.h"
#include "graphics/program/gl_program.h"

gl_uniform_buffer::~gl_uniform_buffer()
{
}

gl_uniform_buffer::gl_uniform_buffer(std::shared_ptr<gl_uniform_buffer_descriptor> descriptor) :
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
		
		const std::size_t _block_size = program.get_uniform_buffer_block_size(_descriptor->get_block_name());
		const auto& _item_layouts = _descriptor->get_item_layouts();

		_buffer = std::make_shared<gl_buffer>();
		_buffer->allocate(_block_size);

		std::size_t _offset = 0;
		for (const auto& _item_layout : _item_layouts)
		{
			_offset = program.get_uniform_buffer_item_offset(_item_layout.name);
			_buffer->fill(_offset, _item_layout.stream.size(), _item_layout.stream.data());
		}

	}
}

void gl_uniform_buffer::_fill_std140()
{
}


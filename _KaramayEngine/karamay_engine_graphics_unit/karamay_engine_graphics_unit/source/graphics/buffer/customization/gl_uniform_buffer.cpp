#include "gl_uniform_buffer.h"

void gl_uniform_buffer::update(std::float_t delta_time)
{
	if (_descriptor && _descriptor->is_dirty())
	{
		if (_descriptor->get_memory_layout() == gl_uniform_buffer_enum::layout::std140)
		{
			_fill_std140();
		}
		else
		{
			_fill_shared_packed();
		}
	}
}

void gl_uniform_buffer::_fill_std140()
{
	// must ensure the buffer was never used

	if (_descriptor)
	{
		const auto _data_size = _descriptor->get_data_size();

		_buffer = std::make_shared<gl_buffer>();
		_buffer->allocate(_data_size);
		_buffer->fill(0,_data_size, _descriptor->get_data());
	}
}


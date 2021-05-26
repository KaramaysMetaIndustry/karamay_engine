#include "gl_uniform_buffer.h"

gl_uniform_buffer::gl_uniform_buffer()
{
}

gl_uniform_buffer::~gl_uniform_buffer()
{
}

void gl_uniform_buffer::update(std::float_t delta_time)
{
	if (_descriptor && _descriptor->is_dirty)
	{
		if (_descriptor->memory_layout == gl_uniform_buffer_enum::layout::std140)
		{
			_fill_std140();
		}
		else
		{
			_fill_shared_packed();
		}
	}
}

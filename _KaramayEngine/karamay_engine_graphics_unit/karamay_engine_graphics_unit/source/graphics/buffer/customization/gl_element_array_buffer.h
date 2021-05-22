#pragma once
#include "graphics/buffer/gl_buffer.h"

class gl_element_array_buffer
{
public:

	gl_element_array_buffer();

	virtual ~gl_element_array_buffer();

private:

	std::shared_ptr<gl_buffer> _ref_buffer;

public:

	void fill(const void* data, std::size_t size)
	{
		_ref_buffer = std::make_shared<gl_buffer>();
		if (_ref_buffer)
		{
			_ref_buffer->allocate(size);
			_ref_buffer->fill(0, size, data);
		}
	}

public:

	void bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ref_buffer->get_handle());
	}

	void unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}


	GLuint get_handle()
	{
		if (_ref_buffer)
			return _ref_buffer->get_handle();

		return 0;
	}

};


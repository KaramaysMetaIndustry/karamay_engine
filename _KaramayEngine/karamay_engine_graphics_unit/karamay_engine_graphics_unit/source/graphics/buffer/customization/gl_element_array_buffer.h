#pragma once
#include "graphics/buffer/gl_buffer.h"


class gl_element_array_buffer_descriptor
{

public:

	void set_indices(const std::vector<std::uint32_t>& indices)
	{
		_data = indices;
	}


	const void* get_data() const
	{
		return (const void*)_data.data();
	}

	const std::size_t get_data_size() const
	{
		return _data.size() * sizeof (glm::uint32);
	}

	const bool is_dirty() const
	{
		return true;
	}

private:

	std::vector<std::uint32_t> _data;


public:
	gl_element_array_buffer_descriptor() {}

	virtual ~gl_element_array_buffer_descriptor() {}
};

class gl_element_array_buffer
{
public:

	gl_element_array_buffer();

	virtual ~gl_element_array_buffer();

private:

	std::shared_ptr<gl_buffer> _buffer;

	std::shared_ptr<gl_element_array_buffer_descriptor> _descriptor;

public:

	void fill(std::shared_ptr<gl_element_array_buffer_descriptor> descriptor)
	{
		_descriptor = descriptor;
		
		if (_descriptor && _descriptor->is_dirty())
		{
			_fill();
		}
	}

private:

	void _fill()
	{
		if (_descriptor)
		{
			_buffer = std::make_shared<gl_buffer>();
			_buffer->allocate(_descriptor->get_data_size());
			_buffer->fill(0, _descriptor->get_data_size(), _descriptor->get_data());
		}
	}

public:

	void bind()
	{
		if(_buffer)
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _buffer->get_handle());
	}

	void unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

};


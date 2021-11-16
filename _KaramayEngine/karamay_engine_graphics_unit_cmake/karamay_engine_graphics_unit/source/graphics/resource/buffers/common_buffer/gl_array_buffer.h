#ifndef GL_ARRAY_BUFFER_H
#define GL_ARRAY_BUFFER_H

#include "graphics/resource/buffers/raw_buffer/gl_buffer.h"

class gl_array_buffer final
{
public:

	gl_array_buffer(int64 bytes_num, const void* initial_data = nullptr)
	{
		_allocate(bytes_num, initial_data);
	}

	gl_array_buffer(const gl_array_buffer&) = delete;
	gl_array_buffer& operator=(const gl_array_buffer&) = delete;

	~gl_array_buffer() = default;

public:

	void reallocate(int64 bytes_num, const void* initial_data = nullptr)
	{
		_allocate(bytes_num, initial_data);
	}

	void write(int64 byte_offset, const void* data, int64 bytes_num)
	{
		if (!_raw_buffer) return;
		_raw_buffer->write(byte_offset, data, bytes_num);
	}

	const void* read(int64 byte_offset, int64 bytes_num) const
	{
		return _raw_buffer ? _raw_buffer->read(byte_offset, bytes_num) : nullptr;
	}

	const gl_buffer* get_raw() const
	{
		return _raw_buffer.get();
	}

public:

	void bind() const noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, _raw_buffer->get_handle());
	}

	void unbind() const noexcept
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

private:

	std::unique_ptr<gl_buffer> _raw_buffer;

	void _allocate(int64 bytes_num, const void* initial_data)
	{
		gl_buffer_storage_options _options;
		_options.client_storage = false;
		_options.dynamic_storage = true;
		_options.map_read = true;
		_options.map_write = true;
		_options.map_coherent = false;
		_options.map_persistent = false;
		if (initial_data)
		{
			_raw_buffer = std::make_unique<gl_buffer>(_options, bytes_num, initial_data);
		}
		else {
			_raw_buffer = std::make_unique<gl_buffer>(_options, bytes_num);
		}
	}

};


#endif

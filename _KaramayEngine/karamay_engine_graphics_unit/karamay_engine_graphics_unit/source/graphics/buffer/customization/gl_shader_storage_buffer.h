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

	enum class matrix_layout
	{
		row_major,
		column_major
	};
}

class gl_shader_storage_buffer_descriptor
{
public:

	gl_shader_storage_buffer_descriptor() :
		_memory_layout(gl_shader_storage_buffer_enum::layout::std140),
		_matrix_memory_layout(gl_shader_storage_buffer_enum::matrix_layout::row_major),
		_block_name(),
		_data(nullptr),
		_size(0),
		_is_dirty(false)
	{

	}

	virtual ~gl_shader_storage_buffer_descriptor()
	{

	}

	template<typename T>
	void add_variable(T variable)
	{

	}


private:

	gl_shader_storage_buffer_enum::layout _memory_layout;
	
	gl_shader_storage_buffer_enum::matrix_layout _matrix_memory_layout;

	std::string _block_name;

	std::shared_ptr<void> _data;

	std::size_t _size;

	std::uint8_t _is_dirty;

public:

	const std::string& get_block_name() const
	{
		return _block_name;
	}

	const void* get_data() const
	{
		return _data.get();
	}

	const std::size_t get_data_size() const
	{
		return _size;
	}

	const std::uint8_t is_dirty() const
	{
		return _is_dirty;
	}
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

	void set_descriptor(std::shared_ptr<gl_shader_storage_buffer_descriptor> descriptor);

	std::shared_ptr<gl_shader_storage_buffer_descriptor> get_descriptor();

	void update(std::float_t delta_time);

	void bind(std::uint32_t binding)
	{
		glBindBufferRange(GL_SHADER_STORAGE_BUFFER, binding, _buffer->get_handle(), 0, _descriptor->get_data_size());
		_binding = binding;
	}

	void unbind()
	{

	}

private:

	void _fill_std140() {}
	void _fill_std430() {}
	void _fill_packed_shared() {}

};


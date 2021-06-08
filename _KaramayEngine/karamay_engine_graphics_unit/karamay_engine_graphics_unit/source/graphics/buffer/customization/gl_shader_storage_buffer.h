#pragma once
#include "graphics/buffer/gl_buffer.h"
#include "graphics/variable/gl_variable.h"

class gl_program;

namespace gl_shader_storage_buffer_enum
{
	enum class layout
	{
		std140,
		std430
	};

	enum class matrix_layout
	{
		row_major,
		column_major
	};
}


struct gl_shader_storage_buffer_item_layout
{
	std::string name;
	std::vector<std::uint8_t> stream;
};

class gl_shader_storage_buffer_descriptor final
{
public:

	gl_shader_storage_buffer_descriptor() :
		_memory_layout(gl_shader_storage_buffer_enum::layout::std140),
		_matrix_memory_layout(gl_shader_storage_buffer_enum::matrix_layout::row_major),
		_block_name(),
		_is_dirty(false)
	{

	}

	template<typename T>
	void add_variable(std::shared_ptr<gl_variable<T>> variable)
	{
		if (variable)
		{
			const std::uint8_t* _variable_bytes
				= reinterpret_cast<const std::uint8_t*>(glm::value_ptr(variable->get_value()));
			const std::size_t _variable_size = variable->get_size();

			gl_shader_storage_buffer_item_layout _item_layout;
			_item_layout.name = variable->get_name();

			for (std::size_t _index = 0; _index < _variable_size;
				_item_layout.stream.push_back(_variable_bytes[_index]), ++_index)
			{}

			_item_layouts.push_back(_item_layout);
		}
	}

private:

	gl_shader_storage_buffer_enum::layout _memory_layout;
	
	gl_shader_storage_buffer_enum::matrix_layout _matrix_memory_layout;

	std::vector<gl_shader_storage_buffer_item_layout> _item_layouts;

	std::string _block_name;

	std::uint8_t _is_dirty;

public:

	const std::vector<gl_shader_storage_buffer_item_layout> get_descriptor() const
	{
		return _item_layouts;
	}

	const std::string& get_block_name() const
	{
		return _block_name;
	}

	const std::uint8_t is_dirty() const
	{
		return _is_dirty;
	}
};


class gl_shader_storage_buffer final
{
public:

	gl_shader_storage_buffer(std::shared_ptr<gl_shader_storage_buffer_descriptor> descriptor)
	{
		_descriptor = descriptor;
	}

private:

	std::shared_ptr<gl_shader_storage_buffer_descriptor> _descriptor;

	std::shared_ptr<gl_buffer> _buffer;

	std::uint32_t _binding;

public:

	void set_descriptor(std::shared_ptr<gl_shader_storage_buffer_descriptor> descriptor);

	std::shared_ptr<gl_shader_storage_buffer_descriptor> get_descriptor();

	void bind(std::uint32_t binding);

	void unbind()
	{

	}

private:

	void _fill_std140() 
	{
		if (_descriptor)
		{
			const std::size_t _block_size = 0;
			const auto& _item_layouts = _descriptor->get_descriptor();

			_buffer = std::make_shared<gl_buffer>();
			_buffer->allocate(_block_size);

			std::size_t _offset = 0;
			for (const auto& _item_layout : _item_layouts)
			{
				_offset;
				_buffer->fill(_offset, _item_layout.stream.size(), _item_layout.stream.data());
			}
		}
	}
	void _fill_std430() {}

public:

	~gl_shader_storage_buffer();

};


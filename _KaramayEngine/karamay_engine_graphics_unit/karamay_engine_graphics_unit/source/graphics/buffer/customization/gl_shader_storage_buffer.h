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

class gl_shader_storage_buffer_descriptor final
{
public:

	gl_shader_storage_buffer_descriptor();

public:

	void add_variable(const std::shared_ptr<gl_variable>& variable);

	void add_variables(const std::vector<std::shared_ptr<gl_variable>>& items)
	{
		_items.insert(_items.cend(), items.cbegin(), items.cend());
	}

	void clear_variables()
	{
		_items.clear();
	}

private:
	
	gl_shader_storage_buffer_enum::layout _memory_layout;
	
	gl_shader_storage_buffer_enum::matrix_layout _matrix_memory_layout;

	std::string _block_name;

	std::vector<std::shared_ptr<gl_variable>> _items;

	std::uint8_t _is_dirty;

public:

	auto get_memory_layout() const { return _memory_layout; }

	auto get_matrix_memory_layout() const { return _matrix_memory_layout; }

	const std::string& get_block_name() const
	{
		return _block_name;
	}

	const std::size_t get_block_size() const
	{
		std::size_t _block_size = 0;
		for (const auto& _item : _items)
		{
			_block_size += _item->get_value().size();
		}
		return _block_size;
	}

	void set_block_name(const std::string& block_name)
	{
		_block_name = block_name;
	}

	const auto& get_items() const
	{
		return _items;
	}

	const std::uint8_t is_dirty() const
	{
		return _is_dirty;
	}

	void set_dirty(std::uint8_t is_dirty)
	{
		_is_dirty = is_dirty;
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

	std::shared_ptr<gl_shader_storage_buffer_descriptor> get_descriptor();

	void bind(std::uint32_t binding);

	void unbind()
	{
		glBindBuffer(GL_SHADER_STORAGE_BUFFER, 0);
	}

private:

	void _fill_std140() 
	{
		
	}

	void _fill_std430()
	{
		if (_descriptor)
		{
			const std::size_t _block_size = _descriptor->get_block_size();

			_buffer = std::make_shared<gl_buffer>();
			_buffer->allocate(_block_size);

			std::size_t _offset = 0;
			for (const auto& _item : _descriptor->get_items())
			{
				if (_item)
				{
					_buffer->fill(_offset, _item->get_value().size(), _item->get_value().data());
					_offset += _item->get_value().size();
				}
			}
		}
	}

public:

	~gl_shader_storage_buffer();

};


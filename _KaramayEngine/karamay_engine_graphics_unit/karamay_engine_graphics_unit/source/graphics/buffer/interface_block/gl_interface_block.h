#pragma once

#include "public/stl.h"

class gl_interface_block_item
{
public:

	gl_interface_block_item(const std::string& type, const std::string& name) :
		_type(type),
		_name(name),
		_stream_size(_get_type_size(type))
	{
		_stream.resize(_stream_size);
	}

	void set_value(const std::vector<std::uint8_t>& stream)
	{
		if (stream.size() != _stream_size) return;
		
		_stream = stream;
	}

private:

	const std::string _type;

	const std::string _name;

	const std::size_t _stream_size;

	std::vector<std::uint8_t> _stream;

public:

	inline const std::string& get_type() const { return _type; }

	inline const std::string& get_name() const { return _name; }

	const std::size_t get_size() const
	{
		return _stream.size();
	}

	const std::uint8_t* get_data() const
	{
		return _stream.data();
	}

private:

	std::size_t _get_type_size(const std::string& type) { return 0; }

};

class gl_interface_block_item_static_array
{
public:

	gl_interface_block_item_static_array(const std::string& type, const std::string& array_name, const std::size_t capacity) :
		_array_name(array_name),
		_max_index(capacity - 1)
	{
		_items.reserve(capacity);

		for(std::size_t _index = 0; _index < capacity; ++_index)
		{
			gl_interface_block_item _item(type, array_name + "[" + std::to_string(_index) + "]");
			_items.push_back(_item);
		}
	}

	void set_item_value(std::uint32_t index, const std::vector<std::uint8_t>& stream)
	{
		if (index > _max_index) return;

		_items.at(index).set_value(stream);
	}

private:

	const std::string _array_name;

	const std::size_t _max_index; // ±‹√‚runtimeº∆À„ capacity - 1

	std::vector<gl_interface_block_item> _items;

	std::vector<std::uint8_t> _array_stream;

	std::vector<std::size_t> _item_offsets;

	std::vector<std::uint32_t> _dirty_indices;
	
public:

	const std::uint8_t* get_item_data(std::uint8_t index)
	{
		return _items[index].get_data();
	}

	const std::size_t get_item_data_size(std::uint8_t index)
	{
		return _items[index].get_size();
	}

	const std::uint8_t* get_array_data()
	{
		_update_array_stream();
		return _array_stream.data();
	}

	const std::size_t get_array_data_size()
	{
		_update_array_stream();
		return _array_stream.size();
	}

private:
	
	void _update_array_stream()
	{
		if (_dirty_indices.size() == 0) return;

		for (const auto _dirty_index : _dirty_indices)
		{
			if (_dirty_index > _max_index) continue;

			
		}

		_dirty_indices.clear();
	}

};

class gl_interface_block_item_dynamic_array
{
public:

	gl_interface_block_item_dynamic_array()
	{

	}


private:

	const std::string _array_name;

};

class gl_interface_block
{
protected:
	gl_interface_block(const std::string& block_name, 
		const std::vector<gl_interface_block_item>& items, 
		const std::vector<gl_interface_block_item_static_array>& item_static_arrays,
		const std::vector<gl_interface_block_item_dynamic_array>& item_dynamic_arrays) :
		_block_name(block_name),
		_items_num(items.size()),
		_item_static_arrays_num(item_static_arrays.size()),
		_item_dynamic_arrays_num(item_dynamic_arrays.size())
	{

	}

	class gl_interface_block_instance {};


protected:

	const std::string _block_name;

	const std::size_t _items_num, _item_static_arrays_num, _item_dynamic_arrays_num;

	const std::vector<std::string> referenced_shaders;

	std::unordered_map<std::string, gl_interface_block_item> _items_map;
	
	std::unordered_map<std::string, gl_interface_block_item_static_array> _item_static_arrays_map;
	
	std::unordered_map<std::string, gl_interface_block_item_dynamic_array> _item_dynamic_arrays_map;

};

class gl_interface_block_instance_static_array
{
public:

};

class gl_interface_block_instance_dynamic_array
{

};


class gl_interface_block_stub
{

};


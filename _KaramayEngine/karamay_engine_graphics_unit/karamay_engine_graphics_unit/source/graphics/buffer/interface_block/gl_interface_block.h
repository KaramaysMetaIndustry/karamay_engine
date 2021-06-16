#pragma once

#include "public/stl.h"

class gl_interface_block_item
{

public:

	gl_interface_block_item(const std::string& item_name, const std::size_t stream_size) :
		_item_name(item_name),
		_stream_size(stream_size)
	{
		_stream.resize(stream_size);
	}

	gl_interface_block_item(const std::string& item_name, const std::vector<std::uint8_t>& stream) :
		_item_name(item_name),
		_stream_size(stream.size()),
		_stream(stream)
	{}

private:

	const std::string _item_name;

	const std::size_t _stream_size;

	std::vector<std::uint8_t> _stream;

};

class gl_interface_block_item_static_array
{
public:

	gl_interface_block_item_static_array(const std::string& item_static_array_name)
	{

	}

private:


};

class gl_interface_block_item_dynamic_array
{

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


protected:

	const std::string _block_name;

	const std::size_t _items_num, _item_static_arrays_num, _item_dynamic_arrays_num;

	std::unordered_map<std::string, gl_interface_block_item> _items_map;
	
	std::unordered_map<std::string, gl_interface_block_item_static_array> _item_static_arrays_map;
	
	std::unordered_map<std::string, gl_interface_block_item_dynamic_array> _item_dynamic_arrays_map;

};


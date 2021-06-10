#pragma once
#include "graphics/buffer/gl_buffer.h"
#include "graphics/variable/gl_variable.h"

class gl_program;

std::size_t _get_type_size(const std::string& type)
{
	if (type == "int") return sizeof glm::ivec1;
	if (type == "ivec2") return sizeof glm::ivec2;
	if (type == "ivec3") return sizeof glm::ivec3;
	if (type == "ivec4") return sizeof glm::ivec4;

	if (type == "uint") return sizeof glm::uvec1;
	if (type == "uvec2") return sizeof glm::uvec2;
	if (type == "uvec3") return sizeof glm::uvec3;
	if (type == "uvec4") return sizeof glm::uvec4;

	if (type == "float") return sizeof glm::vec1;
	if (type == "vec2") return sizeof glm::vec2;
	if (type == "vec3") return sizeof glm::vec3;
	if (type == "vec4") return sizeof glm::vec4;

	if (type == "mat2") return sizeof glm::mat2;
	if (type == "mat3") return sizeof glm::mat3;
	if (type == "mat4") return sizeof glm::mat4;
	if (type == "mat2x3") return sizeof glm::mat2x3;
	if (type == "mat2x4") return sizeof glm::mat2x4;
	if (type == "mat3x2") return sizeof glm::mat3x2;
	if (type == "mat3x4") return sizeof glm::mat3x4;
	if (type == "mat4x2") return sizeof glm::mat4x2;
	if (type == "mat4x3") return sizeof glm::mat4x3;

	if (type == "double") return sizeof glm::dvec1;
	if (type == "dvec2") return sizeof glm::vec2;
	if (type == "dvec3") return sizeof glm::vec3;
	if (type == "dvec4") return sizeof glm::vec4;

	if (type == "dmat2") return sizeof glm::dmat2;
	if (type == "dmat3") return sizeof glm::dmat3;
	if (type == "dmat4") return sizeof glm::dmat4;
	if (type == "dmat2x3") return sizeof glm::dmat2x3;
	if (type == "dmat2x4") return sizeof glm::dmat2x4;
	if (type == "dmat3x2") return sizeof glm::dmat3x2;
	if (type == "dmat3x4") return sizeof glm::dmat3x4;
	if (type == "dmat4x2") return sizeof glm::dmat4x2;
	if (type == "dmat4x3") return sizeof glm::dmat4x3;

	return 0;
}

struct _shader_point_light_std140
{
	// ...
	glm::vec3 position; // Position of the point light
	float __DUMMY_PADDING0__; // This is just needed because of std140 layout padding rules

	glm::vec3 color; // Color of the point light
	float ambientFactor; // Ambient factor (how much this light contributes to the global lighting in any case)

	float constantAttenuation; // Constant attenuation factor of light with rising distance
	float linearAttenuation; // Lienar attenuation factor of light with rising distance
	float exponentialAttenuation; // Constant attenuation factor of light with rising distance
	GLint isOn; // Flag telling, if the light is on
};

namespace gl_uniform_buffer_enum
{
	enum class layout
	{
		std140, // 标准布局
		shared, // 可共享 default
		packed, // 最小化存储，禁止共享
	};

	enum class matrix_layout
	{
		row_major, // uniform buffer 中的matrix 按照 行 存储
		column_major // 按照 列 存储 default
	};
}

class gl_uniform_buffer_descriptor
{

public:

	gl_uniform_buffer_descriptor();

public:

	void add_uniform(const std::shared_ptr<gl_variable>& item);

	void add_uniforms(const std::vector<std::shared_ptr<gl_variable>>& items)
	{
		_items.insert(_items.cend(), items.cbegin(), items.cend());
		_is_dirty = true;
	}

	void clear_uniforms();

private:

	gl_uniform_buffer_enum::layout _memory_layout;

	gl_uniform_buffer_enum::matrix_layout _memory_matrix_layout;

	std::string _block_name;

	std::vector<std::shared_ptr<gl_variable>> _items;

	std::uint8_t _is_dirty;

public:
	
	inline const gl_uniform_buffer_enum::layout get_memory_layout() const
	{
		return _memory_layout;
	}

	inline const std::string& get_block_name() const
	{
		return _block_name;
	}

	inline const auto& get_items()
	{
		return _items;
	}

	inline const std::uint8_t is_dirty() const
	{
		return _is_dirty;
	}

	inline void set_dirty(bool dirty) { _is_dirty = dirty; }

	inline void set_block_name(const std::string& block_name) { _block_name = block_name; }

};

class gl_uniform_buffer_item
{
public:

	gl_uniform_buffer_item(
		const std::string& type, 
		const std::string& name) :
		_type(type),
		_name(name),
		_capacity(_get_type_size(type))
	{
		_stream.resize(_capacity);
	}

public:

	void set_value(const std::vector<std::uint8_t> stream)
	{
		if (stream.size() != _capacity)
			throw std::exception("");
		_stream = stream;
	}

private:

	const std::string _type;
	
	const std::string _name;
	
	const std::size_t _capacity;
	
	std::vector<std::uint8_t> _stream;
	
};

class gl_uniform_buffer_item_array
{

public:

	gl_uniform_buffer_item_array(
		const std::string& type, 
		const std::string& item_array_name) :
		_item_array_name(item_array_name),
		_item_capacity(_get_type_size(type))
	{
	}

public:

	void set_values(const std::vector<std::vector<std::uint8_t>>& streams)
	{
	
	}
	
private:

	const std::string _item_array_name;

	const std::size_t _item_capacity;

	std::vector<gl_uniform_buffer_item> _array;
};

class gl_uniform_buffer_instance
{
public:

	gl_uniform_buffer_instance(
		gl_uniform_buffer_enum::layout layout,
		const std::string& instance_name, 
		const std::vector<gl_uniform_buffer_item>& items,
		const std::vector<gl_uniform_buffer_item_array>& item_arrays) :
		_layout(layout),	
		_instance_name(instance_name),
		_binding(0)
	{
	}

public:

	// data update granules (single item)
	void set_item_value(const std::string& item_name, const gl_uniform_buffer_item& item)
	{}

	// data update granules (single item array)
	void set_item_array_value(const std::string& item_array_name, const std::vector<gl_uniform_buffer_item>& item_array)
	{
		auto _iterator = _item_arrays_map.find(item_array_name);
		if (_iterator == _item_arrays_map.cend())
		{
			throw std::exception("can not find the item_array");
		}

		//_iterator->second = 
	}

	void set_binding(std::uint32_t binding)
	{
		_binding = binding;
	}

private:

	const gl_uniform_buffer_enum::layout _layout;

	const std::string _instance_name;

	std::uint32_t _binding;

	std::unordered_map<std::string, gl_uniform_buffer_item> _items_map;

	std::unordered_map<std::string, gl_uniform_buffer_item_array> _item_arrays_map;

	std::shared_ptr<gl_buffer> _buffer;

};

class gl_uniform_buffer_instance_array
{

public:

	gl_uniform_buffer_instance_array(const std::string& suffix_instance_name)
	{

	}


public:



private:

	std::uint32_t _binding;

	std::vector<gl_uniform_buffer_instance> _array;
};

class gl_uniform_buffer final
{
public:
	
	gl_uniform_buffer(const std::shared_ptr<gl_uniform_buffer_descriptor>& descriptor);

public:

	void bind(std::int32_t binding, gl_program& program);

	void unbind();

	std::shared_ptr<gl_uniform_buffer_descriptor> get_descriptor()
	{
		return _descriptor;
	}

private:

	std::shared_ptr<gl_uniform_buffer_descriptor> _descriptor;

	std::shared_ptr<gl_buffer> _buffer;

	std::uint32_t _binding;

private:

	void _fill_shared_packed(const gl_program& program);

	void _fill_std140();

public:

	~gl_uniform_buffer();



public:



private:

	std::unordered_map<std::string, std::shared_ptr<gl_uniform_buffer_instance>> _instances_map;

	std::unordered_map<std::string, std::shared_ptr<gl_uniform_buffer_instance_array>> _instance_arrays_map;

public:

	auto get_instance(const std::string& instance_name)
	{
		auto _iterator = _instances_map.find(instance_name);
		if (_iterator == _instances_map.cend())
			throw std::exception("");

		return std::weak_ptr<gl_uniform_buffer_instance>(_iterator->second);
	}

	auto get_instance_array(const std::string& instance_array_name)
	{
		auto _iterator = _instance_arrays_map.find(instance_array_name);
		if (_iterator == _instance_arrays_map.cend())
			throw std::exception("");

		return std::weak_ptr<gl_uniform_buffer_instance_array>(_iterator->second);
	}

};


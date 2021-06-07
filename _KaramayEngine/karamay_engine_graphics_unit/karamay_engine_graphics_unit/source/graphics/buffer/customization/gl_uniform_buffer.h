#pragma once
#include "graphics/buffer/gl_buffer.h"
#include "graphics/variable/gl_variable.h"

class gl_program;

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
		row_major, // uniform buffe 中的matrix 按照 行 存储
		column_major // 按照 列 存储 default
	};
}


struct gl_uniform_buffer_item_layout
{
	std::string name;
	std::vector<std::uint8_t> stream;
	
};

class gl_uniform_buffer_descriptor
{

public:

	gl_uniform_buffer_descriptor() :
		_memory_layout(gl_uniform_buffer_enum::layout::packed),
		_memory_matrix_layout(gl_uniform_buffer_enum::matrix_layout::row_major),
		_block_name(),
		_is_dirty(true)
	{

	}

	template<typename T>
	void add_uniform(std::shared_ptr<gl_variable<T>> uniform)
	{
		if (uniform)
		{
			const std::uint8_t* _uniform_bytes = (std::uint8_t*)glm::value_ptr(uniform->get_value());
			const size_t _uniform_size = uniform->get_size();

			gl_uniform_buffer_item_layout _item_layout;
			_item_layout.name = uniform->get_name();
			auto& _stream = _item_layout.stream;

			for (std::size_t _index = 0; _index < _uniform_size; _stream.push_back(_uniform_bytes[_index]), ++_index) {}
			_item_layouts.push_back(_item_layout);
		}
		
	}

	//template<typename T>
	void modify_uniform(const std::string& name, std::shared_ptr<gl_variable<glu_f32vec4>> uniform)
	{
		auto _it = 
		_item_layouts_map.find(name);
		if (_it == _item_layouts_map.cend()) return;

		if (uniform)
		{
			const std::uint8_t* _uniform_bytes = (std::uint8_t*)glm::value_ptr(uniform->get_value());
			const size_t _uniform_size = uniform->get_size();

			gl_uniform_buffer_item_layout _item_layout;
			_item_layout.name = uniform->get_name();
			auto& _stream = _item_layout.stream;

			for (std::size_t _index = 0; _index < _uniform_size; 
				_stream.push_back(_uniform_bytes[_index]), ++_index) {}
		}


	}

private:

	gl_uniform_buffer_enum::layout _memory_layout;

	gl_uniform_buffer_enum::matrix_layout _memory_matrix_layout;

	std::vector<gl_uniform_buffer_item_layout> _item_layouts;

	std::unordered_map<std::string, gl_uniform_buffer_item_layout> _item_layouts_map;

	std::string _block_name;

	std::uint8_t _is_dirty;

public:
	
	inline const std::string& get_block_name() const
	{
		return _block_name;
	}
	
	inline const std::vector<gl_uniform_buffer_item_layout>& get_item_layouts() const
	{
		return _item_layouts;
	}

	inline const gl_uniform_buffer_enum::layout get_memory_layout() const
	{
		return _memory_layout;
	}

	inline const std::uint8_t is_dirty() const
	{
		return _is_dirty;
	}

	inline void set_dirty(bool dirty) { _is_dirty = dirty; }

	inline void set_block_name(const std::string& block_name) { _block_name = block_name; }
};


class gl_uniform_buffer final
{
public:
	
	gl_uniform_buffer(std::shared_ptr<gl_uniform_buffer_descriptor> descriptor);

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

};


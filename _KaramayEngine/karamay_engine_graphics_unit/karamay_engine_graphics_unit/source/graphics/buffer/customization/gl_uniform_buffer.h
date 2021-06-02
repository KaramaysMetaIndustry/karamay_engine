#pragma once
#include "graphics/buffer/gl_buffer.h"
#include "graphics/variable/gl_variable.h"

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


class gl_uniform_buffer_element_layout
{
	std::size_t _offset;
	std::vector<std::uint8_t> _data;

};


class gl_uniform_buffer_descriptor
{

public:

	gl_uniform_buffer_descriptor() :
		_memory_layout(gl_uniform_buffer_enum::layout::std140),
		_memory_matrix_layout(gl_uniform_buffer_enum::matrix_layout::row_major),
		_block_name(),
		_data(),
		_size(0),
		_is_dirty(true)
	{

	}

	template<typename T>
	void add_uniform(T uniform)
	{
		const size_t _uniform_size = sizeof(T);
		const std::uint8_t* _ref = (std::uint8_t*)glm::value_ptr(uniform);
		
		// fill data
		for (std::size_t i = 0; i < _uniform_size; ++i)
			_data.push_back(_ref[i]);
		
		// fill padding
		/*if (_tail < _tmp_size)
		{
			_data.insert(_data.cbegin(), _tail, 0);
		}*/

		std::cout << "container size：" << _data.size() << std::endl;
	}


private:

	gl_uniform_buffer_enum::layout _memory_layout;

	gl_uniform_buffer_enum::matrix_layout _memory_matrix_layout;

	std::unordered_map<std::string, std::shared_ptr<void>> _uniforms_map;

	std::string _block_name;

	std::vector<std::uint8_t> _data;

	std::size_t _size;
	
	std::uint8_t _is_dirty;

public:

	const gl_uniform_buffer_enum::layout get_memory_layout() const
	{
		return _memory_layout;
	}

	const std::string& get_block_name() const
	{
		return _block_name;
	}

	void* get_data()
	{
		return _data.data();
	}

	const std::size_t get_data_size() const
	{
		return _data.size();
	}
	
	const std::uint8_t is_dirty() const
	{
		return _is_dirty;
	}
};


class gl_uniform_buffer final
{

public:
	
	gl_uniform_buffer(std::shared_ptr<gl_uniform_buffer_descriptor> descriptor) :
		_descriptor(descriptor)
	{}
	
	~gl_uniform_buffer()
	{}

public:

	std::shared_ptr<gl_uniform_buffer_descriptor> get_descriptor() { return _descriptor; }

	void update(std::float_t delta_time);

	void bind(std::int32_t binding)
	{
		if (_descriptor && _buffer)
		{
			glBindBufferRange(GL_UNIFORM_BUFFER, binding, _buffer->get_handle(), 0, _descriptor->get_data_size());
		}
	}

	void unbind()
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, _binding, 0, 0, 0);
		_binding = 0;
	}

private:

	std::shared_ptr<gl_uniform_buffer_descriptor> _descriptor;

	std::shared_ptr<gl_buffer> _buffer;

	std::uint32_t _binding;

private:

	void _fill_std140();
	void _fill_shared_packed()
	{

		std::vector<std::string> names;

		//gl_variable<glm::vec3>() a;

		std::size_t _block_size = 0;
		std::size_t _offset = 0;
		std::size_t _size = 0;
		std::vector<std::uint32_t> _data;

		_buffer->allocate(_block_size);
		_buffer->fill(_offset, _data.size(), _data.data());
	}

};


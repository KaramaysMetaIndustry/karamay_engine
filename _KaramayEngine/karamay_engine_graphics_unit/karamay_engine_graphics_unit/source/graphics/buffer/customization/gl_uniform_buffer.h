#pragma once
#include "graphics/buffer/gl_buffer.h"

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
		shared,
		packed,
		std140
	};
}


struct gl_uniform_buffer_layout
{
	//gl_uniform_buffer_enum::layout m_layout;


};



class gl_uniform_buffer
{

public:
	
	gl_uniform_buffer();
	
	virtual ~gl_uniform_buffer();

private:

	std::string _block_name;

	size_t _size;

	size_t _offset;

	std::shared_ptr<gl_buffer> _referred_buffer;

	std::uint32_t _binding;

public:

	void fill(const void* data, size_t size, const gl_uniform_buffer_layout& uniform_buffer_layout)
	{
		// try to get an available buffer and current offset
		_referred_buffer = std::make_shared<gl_buffer>();
		_offset = 0;

		// fill
		if (_referred_buffer)
		{
			_referred_buffer->fill(_offset, size, data);
		}
	}

	void release()
	{
		if (_referred_buffer)
		{
		}
	}

	void bind(std::int32_t binding)
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, binding, _referred_buffer->get_handle(), _offset,  _size);
		_binding = binding;
	}

	void unbind()
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, _binding, 0, 0, 0);
		_binding = 0;
	}

	const std::string& get_block_name() const
	{
		return _block_name;
	}

private:

	void _generate_template_code()
	{
		std::regex pattern("layout(binding = 0, std430) uniform Matrices {}");
	}

	void _fill_std140(const void* data, size_t size)
	{

	}

	void _fill_std430(const void* data)
	{

	}

};


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



gl_buffer_referenece get_buffer_ref()
{
	auto buffer = std::make_shared<gl_buffer>();
}

class gl_uniform_buffer
{

public:
	
	gl_uniform_buffer();
	
	virtual ~gl_uniform_buffer();

private:

	gl_buffer_referenece _buffer_ref;

public:

	void fill_std140(const void* data, const std::vector<std::string>& names)
	{
		_buffer_ref.fill(data);

		fill_std140(data, { "mat4 projection;", "mat4 view;" });

	}

	void bind(std::int32_t binding)
	{
		glBindBufferRange(GL_UNIFORM_BUFFER, binding, _buffer_ref._buffer->get_handle(), _buffer_ref._offset, _buffer_ref._size);
	}

private:

	void _generate_template_code()
	{
		std::regex pattern("layout(binding = 0, std430) uniform Matrices {}");
	}

};


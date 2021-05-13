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

struct _shader_spot_light_std140 {};

struct _shader_directional_light_std140 {};



template<typename T>
std::pair<const void*, size_t> cal(T value)
{
	return std::make_pair((const void*)(value.get()), sizeof T::element_type);
}


class gl_uniform_buffer
{

public:
	
	gl_uniform_buffer();
	
	virtual ~gl_uniform_buffer();


public:
	
	std::string _name;
	
	size_t _size;
	
	const void* _data;

public:

	void construct(const std::string name, std::pair<const void*, size_t> data)
	{
		_name = name;
		_data = data.first;
		_size = data.second;
	}

};


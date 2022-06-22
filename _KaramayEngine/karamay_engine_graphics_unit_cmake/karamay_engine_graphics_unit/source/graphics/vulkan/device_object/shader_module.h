#ifndef SHADER_MODULE_H
#define SHADER_MODULE_H
#include "device_object.h"

class vk_shader_module final : public device_object<VkShaderModule>
{
	void _deallocate() noexcept;

public:

	vk_shader_module(vk_device& dev) 
		: device_object(dev)
	{}

	vk_shader_module(const vk_shader_module&) = delete;
	vk_shader_module& operator=(const vk_shader_module&) = delete;

	~vk_shader_module() override
	{
		_deallocate();
	}

	bool allocate(const vk_shader_module_parameters& parameters) noexcept;

};


#endif
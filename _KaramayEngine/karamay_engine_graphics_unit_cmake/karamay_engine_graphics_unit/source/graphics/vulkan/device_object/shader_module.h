#ifndef SHADER_MODULE_H
#define SHADER_MODULE_H
#include "device_object.h"

class vk_shader_module final : public device_object<VkShaderModule>
{
public:

	vk_shader_module(vk_device& dev);

	vk_shader_module(const vk_shader_module&) = delete;
	vk_shader_module& operator=(const vk_shader_module&) = delete;

	~vk_shader_module() override;

public:

	bool allocate(uint64 size, uint32* code) noexcept;

	void deallocate() noexcept;

};


#endif
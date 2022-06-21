#include "shader_module.h"

vk_shader_module::vk_shader_module(vk_device& dev) : device_object(dev)
{
}

vk_shader_module::~vk_shader_module()
{
	deallocate();
}

bool vk_shader_module::allocate(uint64 size, uint32* code) noexcept
{
	VkShaderModuleCreateInfo _create_info;
	_create_info.sType;
	_create_info.flags;
	_create_info.codeSize = size;
	_create_info.pCode = code;

	vkCreateShaderModule(_dev.handle(), &_create_info, nullptr, &_handle);

	return false;
}

void vk_shader_module::deallocate() noexcept
{
	if (_handle)
	{
		vkDestroyShaderModule(_dev.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

#include "shader_module.h"

bool shader_module::allocate(uint64 size, uint32* code)
{
	VkShaderModuleCreateInfo _create_info;
	_create_info.sType;
	_create_info.flags;
	_create_info.codeSize = size;
	_create_info.pCode = code;

	vkCreateShaderModule(_device.handle(), &_create_info, nullptr, &_handle);

	return false;
}

void shader_module::deallocate()
{
	vkDestroyShaderModule(_device.handle(), _handle, nullptr);
}

#include "shader_module.h"

void vk_shader_module::_deallocate() noexcept
{
	if (_handle)
	{
		vkDestroyShaderModule(_dev.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

bool vk_shader_module::allocate(const vk_shader_module_parameters& parameters) noexcept
{
	vkCreateShaderModule(_dev.handle(), &(parameters.core()), nullptr, &_handle);
	return false;
}



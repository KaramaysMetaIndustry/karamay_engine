#include "sampler.h"

void vk_sampler::_deallocate()
{
	if (_handle)
	{
		vkDestroySampler(_dev.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

bool vk_sampler::allocate(const vk_sampler_parameters& parameters)
{
	if (vkCreateSampler(_dev.handle(), &(parameters.core()), nullptr, &_handle) == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

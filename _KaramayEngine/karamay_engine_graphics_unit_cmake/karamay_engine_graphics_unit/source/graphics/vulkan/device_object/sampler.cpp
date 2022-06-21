#include "sampler.h"

vk_sampler::vk_sampler(vk_device& dev) : device_object(dev)
{
	
}

vk_sampler::~vk_sampler()
{
	if (_handle)
	{
		vkDestroySampler(_dev.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

bool vk_sampler::allocate()
{
	VkSamplerCreateInfo _create_info;
	_create_info.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	_create_info.addressModeU;
	_create_info.addressModeV;
	_create_info.addressModeW;
	_create_info.anisotropyEnable;
	_create_info.borderColor;
	_create_info.compareEnable;
	_create_info.compareOp;
	_create_info.magFilter;
	_create_info.maxAnisotropy;
	_create_info.maxLod;
	_create_info.minFilter;
	_create_info.minLod;
	_create_info.mipLodBias;
	_create_info.mipmapMode;

	if (vkCreateSampler(_dev.handle(), &_create_info, nullptr, &_handle) == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

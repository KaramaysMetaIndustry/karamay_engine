#include "descriptor_pool.h"

descriptor_pool::descriptor_pool(device& dev) : device_object(dev)
{
}

descriptor_pool::~descriptor_pool()
{
	deallocate();
}

bool descriptor_pool::allocate() noexcept
{
	VkDescriptorPoolCreateInfo _create_info{};
	_create_info.sType;
	_create_info.flags;
	_create_info.maxSets;
	_create_info.poolSizeCount;
	_create_info.pPoolSizes;

	vkCreateDescriptorPool(_device.handle(), &_create_info, nullptr, &_handle);

	return true;
}

void descriptor_pool::deallocate() noexcept
{
	if (_handle)
	{
		vkDestroyDescriptorPool(_device.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

void descriptor_pool::reset(VkDescriptorPoolResetFlags flags) noexcept
{
	vkResetDescriptorPool(_device.handle(), _handle, flags);
}

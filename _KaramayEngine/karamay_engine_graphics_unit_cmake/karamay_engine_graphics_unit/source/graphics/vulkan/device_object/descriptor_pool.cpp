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
	deallocate();

	VkDescriptorPoolCreateInfo _create_info{};
	_create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	_create_info.flags;
	_create_info.maxSets;
	_create_info.poolSizeCount;
	_create_info.pPoolSizes;

	auto _result = vkCreateDescriptorPool(_device.handle(), &_create_info, nullptr, &_handle);

	if (_result != VkResult::VK_SUCCESS)
	{
		return false;
	}

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

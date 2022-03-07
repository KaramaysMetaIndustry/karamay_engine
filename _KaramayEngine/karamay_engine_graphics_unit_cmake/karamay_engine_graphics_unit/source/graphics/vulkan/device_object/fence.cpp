#include "fence.h"

fence::fence(device& dev) : device_object(dev)
{
}

fence::~fence()
{
	deallocate();
}

bool fence::allocate() noexcept
{
	VkFenceCreateInfo _create_info;
	_create_info.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;

	auto _result = vkCreateFence(_device.handle(), &_create_info, nullptr, &_handle);
	if (_result != VkResult::VK_SUCCESS)
	{
		return false;
	}
	return true;
}

void fence::deallocate() noexcept
{
	if (_handle)
	{
		vkDestroyFence(_device.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

void fence::wait(bool wait_all, uint64 timeout) noexcept
{
	if (!_handle) return;
	vkWaitForFences(_device.handle(), 1, &_handle, wait_all, timeout);
}

void fence::reset() noexcept
{
	if (!_handle) return;
	vkResetFences(_device.handle(), 1, &_handle);
}

bool fence::status() noexcept
{
	if (!_handle) return false;
	auto _result = vkGetFenceStatus(_device.handle(), _handle);
	
	if (_result == VkResult::VK_SUCCESS)
	{
		return true;
	}
	return false;
}

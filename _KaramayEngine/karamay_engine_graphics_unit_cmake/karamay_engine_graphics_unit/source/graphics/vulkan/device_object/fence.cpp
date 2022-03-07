#include "fence.h"

bool fence::allocate() noexcept
{
	VkFenceCreateInfo _create_info;
	_create_info.sType;
	vkCreateFence(_device.handle(), &_create_info, nullptr, &_handle);

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

void fence::wait(bool wait_all, uint64 timeout)
{
	vkWaitForFences(_device.handle(), 1, &_handle, wait_all, timeout);
}

void fence::reset()
{
	vkResetFences(_device.handle(), 1, &_handle);
}

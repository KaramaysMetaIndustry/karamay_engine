#include "semaphore.h"

semaphore::semaphore(device& dev) : device_object(dev)
{
}

semaphore::~semaphore()
{
	deallocate();
}

bool semaphore::allocate()
{
	VkSemaphoreCreateInfo _create_info;
	_create_info.sType;
	vkCreateSemaphore(_device.handle(), &_create_info, nullptr, &_handle);
	return true;
}

void semaphore::deallocate()
{
	if (_handle)
	{
		vkDestroySemaphore(_device.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

#include "semaphore.h"

semaphore::semaphore(device& dev) : device_object(dev)
{
}

semaphore::~semaphore()
{
	deallocate();
}

bool semaphore::allocate() noexcept
{
	deallocate();

	VkSemaphoreCreateInfo _create_info{};
	_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	auto _result = vkCreateSemaphore(_dev.handle(), &_create_info, nullptr, &_handle);
	if (_result != VkResult::VK_SUCCESS)
	{
		return false;
	}
	return true;
}

void semaphore::deallocate() noexcept
{
	if (_handle)
	{
		vkDestroySemaphore(_dev.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

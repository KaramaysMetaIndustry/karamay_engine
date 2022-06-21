#include "semaphore.h"

vk_semaphore::vk_semaphore(vk_device& dev) : device_object(dev)
{
}

vk_semaphore::~vk_semaphore()
{
	deallocate();
}

bool vk_semaphore::allocate() noexcept
{
	deallocate();

	VkSemaphoreCreateInfo _create_info{};
	_create_info.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;

	if (vkCreateSemaphore(_dev.handle(), &_create_info, nullptr, &_handle)  == VkResult::VK_SUCCESS)
	{
		return true;
	}
	
	return true;
}

void vk_semaphore::deallocate() noexcept
{
	if (_handle)
	{
		vkDestroySemaphore(_dev.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

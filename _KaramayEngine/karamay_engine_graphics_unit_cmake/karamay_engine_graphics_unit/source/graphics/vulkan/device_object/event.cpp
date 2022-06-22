#include "event.h"

vk_event::vk_event(vk_device& dev) : device_object(dev)
{
}

vk_event::~vk_event()
{
	_deallocate();
}

bool vk_event::allocate() noexcept
{
	VkEventCreateInfo _create_info
	{
		.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO,
	};

	if (vkCreateEvent(_dev.handle(), &_create_info, nullptr, &_handle) == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

void vk_event::set() noexcept
{
	vkSetEvent(_dev.handle(), _handle);
}

void vk_event::reset() noexcept
{
	vkResetEvent(_dev.handle(), _handle);
}

bool vk_event::get_status() noexcept
{
	return vkGetEventStatus(_dev.handle(), _handle) == VkResult::VK_SUCCESS;
}

void vk_event::_deallocate() noexcept
{
	if (_handle) vkDestroyEvent(_dev.handle(), _handle, nullptr);
}

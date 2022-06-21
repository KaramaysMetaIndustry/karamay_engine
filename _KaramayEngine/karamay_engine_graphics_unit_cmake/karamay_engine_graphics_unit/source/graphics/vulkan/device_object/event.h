#ifndef EVENT_H
#define EVENT_H
#include "device_object.h"

class vk_event final : public device_object<VkEvent>
{
public:
	vk_event(device& dev);

	vk_event(const vk_event&) = delete;
	vk_event& operator=(const vk_event&) = delete;
	
	~vk_event() override {}

public:

	bool allocate()
	{
		VkEventCreateInfo _CreateInfo
		{
			.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO
		};

		if (vkCreateEvent(_dev.handle(), &_CreateInfo, nullptr, &_handle) == VkResult::VK_SUCCESS)
		{
			return true;
		}
		return false;
	}

};

#endif
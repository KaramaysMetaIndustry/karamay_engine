#ifndef FENCE_H
#define FENCE_H
#include "device_object.h"

class fence final : public device_object<VkFence>
{
public:

	bool allocate()
	{
		VkFenceCreateInfo _create_info;
		_create_info.sType;
		vkCreateFence(_device.handle(), &_create_info, nullptr, &_handle);

		return true;
	}

	void deallocate()
	{
		vkDestroyFence(_device.handle(), _handle, nullptr);
		_handle = nullptr;
	}

};


#endif
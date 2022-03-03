#ifndef PHYSICAL_DEVICE_H
#define PHYSICAL_DEVICE_H
#include "vulkan_object.h"

class device;

class physical_device final : public vulkan_object<VkPhysicalDevice>
{
public:

	physical_device(VkPhysicalDevice new_handle)
	{
		_handle = new_handle;
	}

public:

	device* create_device();

};

#endif
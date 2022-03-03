#ifndef INSTANCE_H
#define INSTANCE_H
#include "vulkan_object.h"
#include "physical_device.h"

class instance final : public vulkan_object<VkInstance>
{
public:

	instance()
	{
		VkInstanceCreateInfo _create_info;
		_create_info.sType;
		_create_info.pApplicationInfo;
		_create_info.ppEnabledExtensionNames;
		_create_info.ppEnabledLayerNames;
		_create_info.enabledExtensionCount;
		_create_info.enabledLayerCount;
		VkResult _ret = vkCreateInstance(&_create_info, nullptr, &_handle);
	}

public:

	void enumerate_physical_devices(std::vector<physical_device*>& physical_devices);

};

#endif
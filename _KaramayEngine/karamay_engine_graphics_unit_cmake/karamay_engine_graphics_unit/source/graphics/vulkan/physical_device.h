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

	void get_features(VkPhysicalDeviceFeatures& features)
	{
		vkGetPhysicalDeviceFeatures(_handle, &features);
	}

	void get_properties(VkPhysicalDeviceProperties& properties)
	{
		vkGetPhysicalDeviceProperties(_handle, &properties);
	}

	void get_queue_family_properties(std::vector<VkQueueFamilyProperties>& properties)
	{
		uint32 _count = 0;
		vkGetPhysicalDeviceQueueFamilyProperties(_handle, &_count, nullptr);
		if (_count == 0) return;
		properties.resize(_count);
		vkGetPhysicalDeviceQueueFamilyProperties(_handle, &_count, properties.data());
	}

};

#endif
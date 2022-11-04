#ifndef _PHYSICAL_DEVICE_H_
#define _PHYSICAL_DEVICE_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class PhysicalDevice final : public VulkanObject<VkPhysicalDevice>
{
public:
	PhysicalDevice() = default;

	virtual ~PhysicalDevice() = default;

	std::shared_ptr<VkDevice> CreateDevice();

	void GetFeatures(VkPhysicalDeviceFeatures& OutFeatures);

	void GetProperties(VkPhysicalDeviceProperties& OutProperties);

	void GetMemoryProperties(VkPhysicalDeviceMemoryProperties& OutMemoryProperties);

	void GetQueueFamilyProperties(std::vector<VkQueueFamilyProperties>& OutQueueFamilyProperties);

	void EnumerateExtensionProperties(const std::string& PlayerName, std::vector<VkExtensionProperties>& OutExtensionProperties);

	void EnumerateLayerProperties(std::vector<VkLayerProperties>& OutLayerProperties);

};

_KANAS_CORE_END

#endif
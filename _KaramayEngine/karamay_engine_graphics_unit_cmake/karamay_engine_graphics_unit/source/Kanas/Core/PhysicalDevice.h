#ifndef _PHYSICAL_DEVICE_H_
#define _PHYSICAL_DEVICE_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class Device;

class PhysicalDevice final : public VulkanObject<VkPhysicalDevice>
{
public:

	PhysicalDevice();

	virtual ~PhysicalDevice() override;

	void GetFeatures(VkPhysicalDeviceFeatures& OutFeatures);

	void GetProperties(VkPhysicalDeviceProperties& OutProperties);

	void GetMemoryProperties(VkPhysicalDeviceMemoryProperties& OutMemoryProperties);

	void GetQueueFamilyProperties(std::vector<VkQueueFamilyProperties>& OutQueueFamilyProperties);

	void EnumerateExtensionProperties(const std::string& PlayerName, std::vector<VkExtensionProperties>& OutExtensionProperties);

	void EnumerateLayerProperties(std::vector<VkLayerProperties>& OutLayerProperties);

private:

	std::vector<Device*> LogicalGPUs;

};

_KANAS_CORE_END

#endif

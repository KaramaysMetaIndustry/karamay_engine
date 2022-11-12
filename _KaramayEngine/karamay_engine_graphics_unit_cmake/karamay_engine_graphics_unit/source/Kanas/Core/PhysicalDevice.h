#ifndef _PHYSICAL_DEVICE_H_
#define _PHYSICAL_DEVICE_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class VulkanInstance;
class Device;

class PhysicalDevice final : public VulkanObject<VkPhysicalDevice>
{
public:

	PhysicalDevice(VulkanInstance& InInstance, VkPhysicalDevice InHandle);

	virtual ~PhysicalDevice() override;

	void GetFeatures(VkPhysicalDeviceFeatures& OutFeatures);

	void GetProperties(VkPhysicalDeviceProperties& OutProperties);

	void GetMemoryProperties(VkPhysicalDeviceMemoryProperties& OutMemoryProperties);

	void GetQueueFamilyProperties(std::vector<VkQueueFamilyProperties>& OutQueueFamilyProperties);

	void EnumerateExtensionProperties(const std::string& PlayerName, std::vector<VkExtensionProperties>& OutExtensionProperties);

	void EnumerateLayerProperties(std::vector<VkLayerProperties>& OutLayerProperties);


	Device* CreateDevice();

	void DeleteDevice(Device* InDeviceToDelete);

	void GetDevices(TVector<Device*>& OutDevices);

private:

	VulkanInstance& Instance;

	TVector<TUniquePtr<Device>> Devices;

};

_KANAS_CORE_END

#endif

#ifndef _PHYSICAL_DEVICE_H_
#define _PHYSICAL_DEVICE_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class VulkanInstance;
class FDevice;

class FPhysicalDevice final : public VulkanObject<VkPhysicalDevice>
{
public:

	FPhysicalDevice(VulkanInstance& InInstance, VkPhysicalDevice InHandle);

	virtual ~FPhysicalDevice() override;

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

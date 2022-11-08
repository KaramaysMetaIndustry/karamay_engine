#include "PhysicalDevice.h"

Kanas::Core::PhysicalDevice::PhysicalDevice()
{
}

Kanas::Core::PhysicalDevice::~PhysicalDevice()
{
}

void Kanas::Core::PhysicalDevice::GetFeatures(VkPhysicalDeviceFeatures& OutFeatures)
{
	vkGetPhysicalDeviceFeatures(GetHandle(), &OutFeatures);
}

void Kanas::Core::PhysicalDevice::GetProperties(VkPhysicalDeviceProperties& OutProperties)
{
	vkGetPhysicalDeviceProperties(GetHandle(), &OutProperties);
}

void Kanas::Core::PhysicalDevice::GetMemoryProperties(VkPhysicalDeviceMemoryProperties& OutMemoryProperties)
{
	vkGetPhysicalDeviceMemoryProperties(GetHandle(), &OutMemoryProperties);
}

void Kanas::Core::PhysicalDevice::GetQueueFamilyProperties(std::vector<VkQueueFamilyProperties>& OutQueueFamilyProperties)
{
	uint32 Count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(GetHandle(), &Count, nullptr);
	
	OutQueueFamilyProperties.resize(Count);
	vkGetPhysicalDeviceQueueFamilyProperties(GetHandle(), nullptr, OutQueueFamilyProperties.data());
}

void Kanas::Core::PhysicalDevice::EnumerateExtensionProperties(const std::string& PlayerName, std::vector<VkExtensionProperties>& OutExtensionProperties)
{
	uint32 Count = 0;
	vkEnumerateDeviceExtensionProperties(GetHandle(), PlayerName .c_str(), & Count, nullptr);
	
	if (Count > 0)
	{
		OutExtensionProperties.resize(Count);
		vkEnumerateDeviceExtensionProperties(GetHandle(), PlayerName.c_str(), nullptr, OutExtensionProperties.data());
	}
}

void Kanas::Core::PhysicalDevice::EnumerateLayerProperties(std::vector<VkLayerProperties>& OutLayerProperties)
{
	uint32 Count = 0;
	vkEnumerateDeviceLayerProperties(GetHandle(), &Count, nullptr);

	if (Count > 0)
	{
		OutLayerProperties.resize(Count);
		vkEnumerateDeviceLayerProperties(GetHandle(), nullptr, OutLayerProperties.data());
	}
}

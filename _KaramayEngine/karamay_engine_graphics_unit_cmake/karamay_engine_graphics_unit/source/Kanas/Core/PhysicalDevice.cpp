#include "PhysicalDevice.h"
#include "Device.h"
#include "VulkanInstance.h"

Kanas::Core::PhysicalDevice::PhysicalDevice(VulkanInstance& InInstance, VkPhysicalDevice InHandle) :
	Instance(InInstance)
{
	_Handle = InHandle;
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

Kanas::Core::Device* Kanas::Core::PhysicalDevice::CreateDevice()
{
	auto NewDevice = std::make_unique<Device>(*this);

	if (NewDevice && NewDevice->Allocate())
	{
		Devices.emplace_back(NewDevice);
		return NewDevice.get();
	}

	return nullptr;
}

void Kanas::Core::PhysicalDevice::DeleteDevice(Device* InDeviceToDelete)
{
	if (InDeviceToDelete)
	{
		for (auto It = Devices.begin(); It != Devices.end(); ++It)
		{
			if (*It && It->get() == InDeviceToDelete)
			{
				Devices.erase(It);
				break;
			}
		}
	}
}

void Kanas::Core::PhysicalDevice::GetDevices(TVector<Device*>& OutDevices)
{
	OutDevices.reserve(Devices.size());

	for (auto& Dev : Devices)
	{
		if (Dev)
		{
			OutDevices.emplace_back(Dev.get());
		}
	}
}

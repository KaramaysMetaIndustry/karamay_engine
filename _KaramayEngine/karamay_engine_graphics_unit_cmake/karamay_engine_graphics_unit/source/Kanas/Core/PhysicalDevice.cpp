#include "PhysicalDevice.h"
#include "Device.h"
#include "VulkanInstance.h"

Kanas::Core::FPhysicalDevice::FPhysicalDevice(VulkanInstance& InInstance, VkPhysicalDevice InHandle) :
	Instance(InInstance)
{
	_Handle = InHandle;
}

Kanas::Core::FPhysicalDevice::~FPhysicalDevice()
{
}

void Kanas::Core::FPhysicalDevice::GetFeatures(VkPhysicalDeviceFeatures& OutFeatures)
{
	vkGetPhysicalDeviceFeatures(GetHandle(), &OutFeatures);
}

void Kanas::Core::FPhysicalDevice::GetProperties(VkPhysicalDeviceProperties& OutProperties)
{
	vkGetPhysicalDeviceProperties(GetHandle(), &OutProperties);
}

void Kanas::Core::FPhysicalDevice::GetMemoryProperties(VkPhysicalDeviceMemoryProperties& OutMemoryProperties)
{
	vkGetPhysicalDeviceMemoryProperties(GetHandle(), &OutMemoryProperties);

	VK_MAX_MEMORY_HEAPS;
	OutMemoryProperties.memoryHeaps[0].size;
	OutMemoryProperties.memoryHeaps[0].flags;
	VK_MAX_MEMORY_TYPES;
	OutMemoryProperties.memoryTypes[0].heapIndex;
	OutMemoryProperties.memoryTypes[0].propertyFlags;

	VK_MEMORY_HEAP_DEVICE_LOCAL_BIT; // DeviceLocal
	VK_MEMORY_HEAP_MULTI_INSTANCE_BIT; // MultiInstance

	struct FMemoryHeap
	{
		uint32 HeapIndex;
		uint64 HeapSize;
		TVector<FMemoryProperty> Properties;
	};

}

void Kanas::Core::FPhysicalDevice::GetQueueFamilyProperties(std::vector<VkQueueFamilyProperties>& OutQueueFamilyProperties)
{
	uint32 Count = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(GetHandle(), &Count, nullptr);
	
	OutQueueFamilyProperties.resize(Count);
	vkGetPhysicalDeviceQueueFamilyProperties(GetHandle(), nullptr, OutQueueFamilyProperties.data());
}

void Kanas::Core::FPhysicalDevice::EnumerateExtensionProperties(const std::string& PlayerName, std::vector<VkExtensionProperties>& OutExtensionProperties)
{
	uint32 Count = 0;
	vkEnumerateDeviceExtensionProperties(GetHandle(), PlayerName .c_str(), & Count, nullptr);
	
	if (Count > 0)
	{
		OutExtensionProperties.resize(Count);
		vkEnumerateDeviceExtensionProperties(GetHandle(), PlayerName.c_str(), nullptr, OutExtensionProperties.data());
	}
}

void Kanas::Core::FPhysicalDevice::EnumerateLayerProperties(std::vector<VkLayerProperties>& OutLayerProperties)
{
	uint32 Count = 0;
	vkEnumerateDeviceLayerProperties(GetHandle(), &Count, nullptr);

	if (Count > 0)
	{
		OutLayerProperties.resize(Count);
		vkEnumerateDeviceLayerProperties(GetHandle(), nullptr, OutLayerProperties.data());
	}
}

Kanas::Core::FDevice* Kanas::Core::FPhysicalDevice::CreateDevice()
{
	auto NewDevice = std::make_unique<Device>(*this);

	if (NewDevice && NewDevice->Allocate())
	{
		Devices.emplace_back(NewDevice);
		return NewDevice.get();
	}

	return nullptr;
}

void Kanas::Core::FPhysicalDevice::DeleteDevice(Device* InDeviceToDelete)
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

void Kanas::Core::FPhysicalDevice::GetDevices(TVector<FDevice*>& OutDevices)
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

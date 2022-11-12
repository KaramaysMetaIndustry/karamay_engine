#include "VulkanInstance.h"
#include "PhysicalDevice.h"

Kanas::Core::VulkanInstance::VulkanInstance()
{
}

Kanas::Core::VulkanInstance::~VulkanInstance()
{
	if (IsValid())
	{
		vkDestroyInstance(GetHandle(), nullptr);

		ResetHandle();
	}
}

bool Kanas::Core::VulkanInstance::Initialize()
{
	VkApplicationInfo ApplicationInfo;
	ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ApplicationInfo.pNext = nullptr;
	ApplicationInfo.pApplicationName = "";
	ApplicationInfo.applicationVersion = 0;
	ApplicationInfo.pEngineName = "";
	ApplicationInfo.engineVersion;
	ApplicationInfo.apiVersion;

	TVector<const char*> EnabledLayerNames;
	TVector<const char*> EnabledExtensionNames;

	VkInstanceCreateInfo InstanceCreateInfo;
	InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	InstanceCreateInfo.pNext = nullptr;
	InstanceCreateInfo.flags = {};
	InstanceCreateInfo.pApplicationInfo = &ApplicationInfo;
	InstanceCreateInfo.enabledLayerCount = static_cast<uint32>(EnabledLayerNames.size());
	InstanceCreateInfo.ppEnabledLayerNames = EnabledLayerNames.data();
	InstanceCreateInfo.enabledExtensionCount = static_cast<uint32>(EnabledExtensionNames.size());
	InstanceCreateInfo.ppEnabledExtensionNames = EnabledExtensionNames.data();

	const VkResult Result = vkCreateInstance(&InstanceCreateInfo, nullptr, &_Handle);

	if (Result == VK_SUCCESS)
	{

		uint32 PhysicalDeviceCount = 0;
		vkEnumeratePhysicalDevices(GetHandle(), &PhysicalDeviceCount, nullptr);

		TVector<VkPhysicalDevice> PhysicalDeviceHandles;
		PhysicalDeviceHandles.resize(PhysicalDeviceCount);

		vkEnumeratePhysicalDevices(GetHandle(), nullptr, PhysicalDeviceHandles.data());

		for (auto Handle : PhysicalDeviceHandles)
		{
			if (Handle != VK_NULL_HANDLE)
			{
				auto NewPhysicalDevice = std::make_unique<PhysicalDevice>(*this, Handle);
				if (NewPhysicalDevice)
				{
					GPUs.emplace_back(NewPhysicalDevice);
				}
			}
		}

		return true;
	}

	return false;
}

void Kanas::Core::VulkanInstance::GetGPUs(TVector<PhysicalDevice*>& OutGPUs) const
{
	OutGPUs.reserve(GPUs.size());
	for (const auto& GPU : GPUs)
	{
		if (GPU)
		{
			OutGPUs.emplace_back(GPU.get());
		}
	}
}

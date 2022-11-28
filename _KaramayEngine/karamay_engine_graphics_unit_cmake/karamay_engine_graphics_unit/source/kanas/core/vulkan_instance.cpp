#include "vulkan_instance.h"
#include "physical_device.h"

kanas::core::vulkan_instance::vulkan_instance()
{
}

kanas::core::vulkan_instance::~vulkan_instance()
{
	if (IsValid())
	{
		vkDestroyInstance(get_handle(), nullptr);

		reset_handle();
	}
}

bool kanas::core::vulkan_instance::initialize()
{
	VkApplicationInfo ApplicationInfo;
	ApplicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	ApplicationInfo.pNext = nullptr;
	ApplicationInfo.pApplicationName = "";
	ApplicationInfo.applicationVersion = 0;
	ApplicationInfo.pEngineName = "";
	ApplicationInfo.engineVersion;
	ApplicationInfo.apiVersion;

	std::vector<const char*> EnabledLayerNames;
	std::vector<const char*> EnabledExtensionNames;

	VkInstanceCreateInfo InstanceCreateInfo;
	InstanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	InstanceCreateInfo.pNext = nullptr;
	InstanceCreateInfo.flags = {};
	InstanceCreateInfo.pApplicationInfo = &ApplicationInfo;
	InstanceCreateInfo.enabledLayerCount = static_cast<std::uint32_t>(EnabledLayerNames.size());
	InstanceCreateInfo.ppEnabledLayerNames = EnabledLayerNames.data();
	InstanceCreateInfo.enabledExtensionCount = static_cast<std::uint32_t>(EnabledExtensionNames.size());
	InstanceCreateInfo.ppEnabledExtensionNames = EnabledExtensionNames.data();

	const VkResult Result = vkCreateInstance(&InstanceCreateInfo, nullptr, &handle);

	if (Result == VK_SUCCESS)
	{

		std::uint32_t PhysicalDeviceCount = 0;
		vkEnumeratePhysicalDevices(get_handle(), &PhysicalDeviceCount, nullptr);

		std::vector<VkPhysicalDevice> PhysicalDeviceHandles;
		PhysicalDeviceHandles.resize(PhysicalDeviceCount);

		vkEnumeratePhysicalDevices(get_handle(), nullptr, PhysicalDeviceHandles.data());

		for (auto Handle : PhysicalDeviceHandles)
		{
			if (Handle != VK_NULL_HANDLE)
			{
				auto NewPhysicalDevice = std::make_unique<physical_device>(*this, Handle);
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

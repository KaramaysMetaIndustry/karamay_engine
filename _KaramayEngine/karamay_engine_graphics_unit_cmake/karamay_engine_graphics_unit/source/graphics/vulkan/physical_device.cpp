#include "physical_device.h"
#include "device.h"

vk_physical_device::vk_physical_device(VkPhysicalDevice new_handle)
{
    _handle = new_handle;
}

vk_physical_device::~vk_physical_device()
{
}

std::shared_ptr<vk_device> vk_physical_device::create_device() noexcept
{
    auto _obj = std::make_shared<vk_device>(*this);
    if (_obj)
    {
        return _obj;
    }
    return nullptr;
}

void vk_physical_device::enumerate_extension_properties(const std::string& player_name, std::vector<VkExtensionProperties>& properties) noexcept
{
    uint32 _count = 0;
    vkEnumerateDeviceExtensionProperties(_handle, player_name.c_str(), &_count, nullptr);
    if (_count == 0) return;
    properties.resize(_count);
    vkEnumerateDeviceExtensionProperties(_handle, player_name.c_str(), &_count, properties.data());
}

void vk_physical_device::enumerate_layer_properties(std::vector<VkLayerProperties>& properties) noexcept
{
    uint32 _count = 0;
    vkEnumerateDeviceLayerProperties(_handle, &_count, nullptr);
    if (_count == 0) return;
    properties.resize(_count);
    vkEnumerateDeviceLayerProperties(_handle, &_count, properties.data());
}

void vk_physical_device::get_features(VkPhysicalDeviceFeatures& features) noexcept
{
    vkGetPhysicalDeviceFeatures(_handle, &features);
}

void vk_physical_device::get_properties(VkPhysicalDeviceProperties& properties) noexcept
{
    vkGetPhysicalDeviceProperties(_handle, &properties);
}

void vk_physical_device::get_memory_properties(VkPhysicalDeviceMemoryProperties& properties) noexcept
{
    vkGetPhysicalDeviceMemoryProperties(_handle, &properties);
}

void vk_physical_device::get_queue_family_properties(std::vector<VkQueueFamilyProperties>& properties) noexcept
{
    uint32 _count = 0;
    vkGetPhysicalDeviceQueueFamilyProperties(_handle, &_count, nullptr);
    if (_count == 0) return;
    properties.resize(_count);
    vkGetPhysicalDeviceQueueFamilyProperties(_handle, &_count, properties.data());
}

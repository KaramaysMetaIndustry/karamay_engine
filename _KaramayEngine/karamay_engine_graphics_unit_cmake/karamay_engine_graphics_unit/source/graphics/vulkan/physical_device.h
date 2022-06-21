#ifndef PHYSICAL_DEVICE_H
#define PHYSICAL_DEVICE_H
#include "vulkan_object.h"

class device;

class vk_physical_device final : public vulkan_object<VkPhysicalDevice>
{
public:

	vk_physical_device(VkPhysicalDevice new_handle);
	
	vk_physical_device(const vk_physical_device&) = delete;
	vk_physical_device& operator=(const vk_physical_device&) = delete;

	~vk_physical_device();

public:

	std::shared_ptr<device> create_device() noexcept;

public:

	void enumerate_extension_properties(const std::string& player_name, std::vector<VkExtensionProperties>& properties) noexcept;

	void enumerate_layer_properties(std::vector<VkLayerProperties>& properties) noexcept;

	void get_features(VkPhysicalDeviceFeatures& features) noexcept;

	void get_properties(VkPhysicalDeviceProperties& properties) noexcept;

	void get_memory_properties(VkPhysicalDeviceMemoryProperties& properties) noexcept;
	
	void get_queue_family_properties(std::vector<VkQueueFamilyProperties>& properties) noexcept;

};

#endif
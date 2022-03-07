#ifndef PHYSICAL_DEVICE_H
#define PHYSICAL_DEVICE_H
#include "vulkan_object.h"

class physical_device final : public vulkan_object<VkPhysicalDevice>
{
public:

	physical_device(VkPhysicalDevice new_handle);
	
	physical_device(const physical_device&) = delete;
	physical_device& operator=(const physical_device&) = delete;

	~physical_device();

public:

	void enumerate_extension_properties(const std::string& player_name, std::vector<VkExtensionProperties>& properties) noexcept;

	void enumerate_layer_properties(std::vector<VkLayerProperties>& properties) noexcept;

	void get_features(VkPhysicalDeviceFeatures& features) noexcept;

	void get_properties(VkPhysicalDeviceProperties& properties) noexcept;

	void get_memory_properties(VkPhysicalDeviceMemoryProperties& properties) noexcept;
	
	void get_queue_family_properties(std::vector<VkQueueFamilyProperties>& properties) noexcept;

};

#endif
#ifndef INSTANCE_H
#define INSTANCE_H
#include "vulkan_object.h"
#include "physical_device.h"
#include "window/window.h"

// vkGetInstanceProcAddr(_handle, "");

class instance final : public vulkan_object<VkInstance>
{
public:

	instance();

	instance(const instance&) = delete;
	instance& operator=(const instance&) = delete;

	~instance();

public:

	bool allocate() noexcept;
	
	void deallocate() noexcept;

public:

	uint32 enumerate_version() noexcept;

	void enumerate_physical_devices(std::vector<physical_device*>& physical_devices) noexcept;

	void enumerate_physical_device_groups(std::vector<VkPhysicalDeviceGroupProperties>& properties) noexcept;

	void enumerate_extension_properties(const std::string& player_name, std::vector<VkExtensionProperties>& properties) noexcept;

	void enumerate_layer_properties(std::vector<VkLayerProperties>& properties) noexcept;

};

#endif
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

private:

	uint32 _version;

	std::vector<std::unique_ptr<vk_physical_device>> _physical_devices;

	std::vector<VkPhysicalDeviceGroupProperties> _physical_device_groups;

	std::unordered_map<std::string, std::vector<VkExtensionProperties>> _name_to_extension_properties;

	std::vector<VkLayerProperties> _layers;

public:

	bool allocate() noexcept;
	
	void deallocate() noexcept;

public:

	uint32 version() const noexcept { return _version; }

	const auto& physical_devices() const noexcept { return _physical_devices; }

	const auto& physical_device_groups() const noexcept { return _physical_device_groups; }

	const auto& extensions() const noexcept { return _name_to_extension_properties; }

	const auto& layers() const noexcept { return _layers; }

};

#endif
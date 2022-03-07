#include "device.h"
#include "physical_device.h"
#include "device_object/buffer.h"
#include "device_object/buffer_view.h"
#include "device_object/image.h"
#include "device_object/image_view.h"
#include "device_object/command_pool.h"
#include "device_object/pooled_object/command_buffer.h"
#include "device_object/pooled_object/descriptor_set.h"
#include "device_object/descriptor_set_layout.h"
#include "device_object/acceleration_structure.h"
#include "device_object/device_memory.h"
#include "device_object/framebuffer.h"
#include "device_object/pipeline.h"
#include "device_object/pipeline_cache.h"
#include "device_object/pipeline_layout.h"
#include "device_object/render_pass.h"
#include "device_object/sampler.h"
#include "device_object/shader_module.h"

device::device()
{
}

device::~device()
{
    deallocate();
}

bool device::allocate(physical_device* entity) noexcept
{
    if (!entity)
    {
        return false;
    }

    VkDeviceQueueCreateInfo _queue;
    _queue.sType;
    _queue.queueFamilyIndex;
    _queue.queueCount;
    _queue.pQueuePriorities;

    std::vector<VkDeviceQueueCreateInfo> _queues;

    std::vector<VkExtensionProperties> _extenions;
    std::vector<VkLayerProperties> _layers;
    entity->enumerate_extension_properties("", _extenions);
    entity->enumerate_layer_properties(_layers);

    VkPhysicalDeviceFeatures _features; 
    entity->get_features(_features);

    VkDeviceCreateInfo _create_info{};
    _create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    _create_info.enabledExtensionCount;
    _create_info.ppEnabledExtensionNames;
    _create_info.enabledLayerCount;
    _create_info.ppEnabledLayerNames;
    _create_info.queueCreateInfoCount = _queues.size();
    _create_info.pQueueCreateInfos = _queues.data();
    _create_info.pEnabledFeatures = &_features;

    VkResult _result =  vkCreateDevice(entity->handle(), &_create_info, nullptr, &_handle);

    if (_result != VkResult::VK_SUCCESS)
    {
        return false;
    }
    return true;
}

void device::deallocate() noexcept
{
	vkDestroyDevice(_handle, nullptr);
	_handle = nullptr;
}

bool device::wait() noexcept
{
	VkResult _result = vkDeviceWaitIdle(_handle);
    if (_result != VkResult::VK_SUCCESS)
    {
        return false;
    }
	return true;
}

void device::get_descriptor_set_layout_support(VkDescriptorSetLayoutSupport& support) noexcept
{
    VkDescriptorSetLayoutCreateInfo _create_info;
    vkGetDescriptorSetLayoutSupport(_handle, &_create_info, &support);
}

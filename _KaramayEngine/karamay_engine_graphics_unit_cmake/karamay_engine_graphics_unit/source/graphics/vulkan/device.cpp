#include "device.h"
#include "physical_device.h"
#include "device_object/buffer.h"
#include "device_object/image.h"
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
#include "renderers/renderer.h"

vk_device::vk_device(vk_physical_device& entity) : _entity(entity)
{
}

vk_device::~vk_device()
{
    deallocate();
}

bool vk_device::allocate() noexcept
{
    deallocate();

    // costruct queues
    std::vector<VkQueueFamilyProperties> _queue_family_properties;
    _entity.get_queue_family_properties(_queue_family_properties);
    std::vector<VkDeviceQueueCreateInfo> _queues;
    _queues.reserve(_queue_family_properties.size());
    uint32 _family_index = 0;
    std::array<float, 16> _priorities = { 0.8f };
    for (const auto& _queue_family : _queue_family_properties)
    {
        /*VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT;
        VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT;
        VkQueueFlagBits::VK_QUEUE_SPARSE_BINDING_BIT;
        VkQueueFlagBits::VK_QUEUE_TRANSFER_BIT;
        VkQueueFlagBits::VK_QUEUE_PROTECTED_BIT;*/

        VkDeviceQueueCreateInfo _queue{};
        _queue.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        _queue.queueFamilyIndex = _family_index;
        _queue.queueCount = _queue_family.queueCount;
        _queue.pQueuePriorities = _priorities.data();
        
        _queues.push_back(_queue);
        ++_family_index;
        break;
    }

    // construct extensions and layers
    std::vector<VkExtensionProperties> _extensions;
    std::vector<VkLayerProperties> _layers;
    _entity.enumerate_extension_properties("", _extensions);
    _entity.enumerate_layer_properties(_layers);
    std::vector<const char*> _extension_names;
    _extension_names.reserve(_layers.size());
    std::vector<const char*> _layer_names;
    _layer_names.reserve(_layers.size());
    for (const auto& _extension : _extensions)
    {
        _extension_names.push_back(_extension.extensionName);
    }
    for (const auto& _layer : _layers)
    {
        _layer_names.push_back(_layer.layerName);
    }

    // features
    VkPhysicalDeviceFeatures _features; 
    _entity.get_features(_features);

    VkDeviceCreateInfo _create_info{};
    _create_info.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    //_create_info.enabledExtensionCount = _extension_names.size();
    //_create_info.ppEnabledExtensionNames = _extension_names.data();
    _create_info.enabledLayerCount = static_cast<uint32>(_layer_names.size());
    _create_info.ppEnabledLayerNames = _layer_names.data();
    _create_info.queueCreateInfoCount = static_cast<uint32>(_queues.size());
    _create_info.pQueueCreateInfos = _queues.data();
    _create_info.pEnabledFeatures = &_features;

    VkResult _result =  vkCreateDevice(_entity.handle(), &_create_info, nullptr, &_handle);

    if (_result != VkResult::VK_SUCCESS)
    {
        return false;
    }

    return true;
}

void vk_device::deallocate() noexcept
{
    if (_handle)
    {
        vkDestroyDevice(_handle, nullptr);
        _handle = nullptr;
    }
}

bool vk_device::wait() const noexcept
{
    if (!_handle) return false;

	auto _result = vkDeviceWaitIdle(_handle);
    if (_result != VkResult::VK_SUCCESS)
    {
        return false;
    }
	return true;
}

void vk_device::run() noexcept
{
    while (!_should_exit)
    {
        for (auto _renderer : _renderers)
        {
            _renderer->render(0.0f);
        }
    }
}

queue* vk_device::invoke_queue(uint32 family_index, uint32 index) const noexcept
{
    if (family_index >= _queues.size() || index >= _queues[family_index].size()) return nullptr;
    return _queues[family_index][index];
}

void vk_device::get_descriptor_set_layout_support(VkDescriptorSetLayoutSupport& support) noexcept
{
    if (!_handle) return;

    VkDescriptorSetLayoutCreateInfo _create_info{};
    _create_info.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    _create_info.flags;
    _create_info.bindingCount;
    _create_info.pBindings;
    vkGetDescriptorSetLayoutSupport(_handle, &_create_info, &support);
}

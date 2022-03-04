#ifndef RENDERER_H
#define RENDERER_H
#include "graphics/vulkan/instance.h"
#include "graphics/vulkan/device.h"
#include "graphics/vulkan/device_object/buffer.h"
#include "graphics/vulkan/device_object/render_pass.h"
#include "graphics/vulkan/device_object/command_pool.h"
#include "graphics/vulkan/device_object/pooled_object/command_buffer.h"
#include "graphics/vulkan/device_object/framebuffer.h"
#include "graphics/vulkan/device_object/queue.h"

class renderer
{

public:

	bool initialize()
	{
        instance _inst;
        std::vector<physical_device*> _physical_devices;
        _inst.enumerate_physical_devices(_physical_devices);
        auto _main_physical_device = _physical_devices[0];

        std::vector<VkQueueFamilyProperties> _queue_family_properties_collection;
        _main_physical_device->get_queue_family_properties(_queue_family_properties_collection);

        for (const auto& _queue_family_properties : _queue_family_properties_collection)
        {
            _queue_family_properties.queueFlags;
            VkQueueFlagBits::VK_QUEUE_COMPUTE_BIT;
            VkQueueFlagBits::VK_QUEUE_GRAPHICS_BIT;
        }

        auto _main_device = _main_physical_device->create_device();

        queue* _q;
        VkSubmitInfo _submit;
        _q->submit(_submit, nullptr);

        VkSwapchainKHR swapchain;
        VkPresentInfoKHR present_info;
        present_info.swapchainCount = 1;
        present_info.pSwapchains = &swapchain;

	}

};

#endif
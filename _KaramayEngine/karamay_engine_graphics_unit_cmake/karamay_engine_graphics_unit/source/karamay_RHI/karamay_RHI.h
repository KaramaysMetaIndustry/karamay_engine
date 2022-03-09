#ifndef KARAMAY_RHI_H
#define KARAMAY_RHI_H
#include "graphics/vulkan/instance.h"
#include "graphics/vulkan/device.h"
#include "graphics/vulkan/device_object/device_memory.h"
#include "graphics/vulkan/device_object/buffer.h"
#include "graphics/vulkan/device_object/buffer_view.h"
#include "graphics/vulkan/device_object/image.h"
#include "graphics/vulkan/device_object/image_view.h"
#include "graphics/vulkan/renderers/renderer.h"

namespace karamay_RHI
{

    class mesh {};

    class atmosphere {};

    class light {};

    class camera {};

    class scene {};


	class dispatcher final
	{
    public:

        dispatcher() = default;
        
        dispatcher(const dispatcher&) = delete;
        dispatcher& operator=(const dispatcher&) = delete;

        ~dispatcher() = default;

    private:

        // vulkan instance
        instance _inst = {};

        // parallel devices
        std::vector<std::shared_ptr<device>> _invoked_devices;

        std::vector<std::thread> _device_threads;

	public:

		bool initialize() noexcept
		{
            if (!_inst.allocate())
            {
                return false;
            }

            // cache devices
            for (const auto& _physical_device : _inst.physical_devices())
            {
                auto _device = _inst.physical_devices().at(0)->create_device();
                _device->allocate();
                _invoked_devices.push_back(_device);
            }

            // invoke device
            auto _device = _invoked_devices.at(0);

            if (!_device->is_valid())
            {
                return false;
            }

            auto _vertex_buffer = _device->invoke<buffer>();
            _vertex_buffer->allocate(4096u, VkBufferUsageFlagBits::VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT, VkSharingMode::VK_SHARING_MODE_EXCLUSIVE);
            
            auto _position_image = _device->invoke<image>();
            _position_image->allocate(
                VkFormat::VK_FORMAT_R32G32B32_SFLOAT, 
                VkImageType::VK_IMAGE_TYPE_1D, 2, {}, 10, 
                VkImageTiling::VK_IMAGE_TILING_LINEAR, VkImageUsageFlagBits::VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, VkSharingMode::VK_SHARING_MODE_EXCLUSIVE,
                VkSampleCountFlagBits::VK_SAMPLE_COUNT_2_BIT, VkImageLayout::VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, 
                {}
            );

            _vertex_buffer->memory()->execute_handler(0, 4,
                [](uint64 size, void* data)
                {
                    float _v = 2.0f;
                    std::cout << "_v : " << _v << std::endl;
                    std::memcpy(&_v, data, 4);
                    std::cout << "_v : " << _v << std::endl;
                    _v = 11.01f;
                    std::memcpy(data, &_v, 4);
                });

            _vertex_buffer->memory()->execute_handler(0, 4,
                [](uint64 size, void* data)
                {
                    float _v = 0.0f;
                    std::memcpy(&_v, data, 4);
                    std::cout << "_v : " << _v << std::endl;
                });
		}

        void dispatch(float delta_time) noexcept
        {
            for (auto _invoked_device : _invoked_devices)
            {
                _invoked_device->run();
            }
        }

	};
};

#endif
#ifndef KARAMAY_RHI_H
#define KARAMAY_RHI_H
#include "graphics/vulkan/instance.h"
#include "graphics/vulkan/device.h"
#include "graphics/vulkan/device_object/buffer.h"
#include "graphics/vulkan/device_object/device_memory.h"
#include "graphics/vulkan/device_object/image.h"

#include "graphics/vulkan/renderers/renderer.h"

namespace karamay_RHI
{
    class scene
    {

    };


	class dispatcher final
	{
        // vulkan instance
        instance _inst = {};

        // parallel devices
        std::vector<device*> _invoked_devices;

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

            /*if (_device_0_0->is_valid())
            {
                auto _vertex_buffer = _device_0_0->invoke<buffer>();
                _vertex_buffer->allocate(
                    1073741824u,
                    VkBufferUsageFlagBits::VK_BUFFER_USAGE_VERTEX_BUFFER_BIT,
                    VkSharingMode::VK_SHARING_MODE_EXCLUSIVE
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

                _device_0_0->deallocate();
            }*/

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
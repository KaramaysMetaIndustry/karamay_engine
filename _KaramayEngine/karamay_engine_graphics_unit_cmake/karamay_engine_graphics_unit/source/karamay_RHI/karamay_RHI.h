#ifndef KARAMAY_RHI_H
#define KARAMAY_RHI_H
#include "graphics/vulkan/instance.h"
#include "graphics/vulkan/device.h"
#include "graphics/vulkan/device_object/device_memory.h"
#include "graphics/vulkan/device_object/buffer.h"
#include "graphics/vulkan/device_object/image.h"
#include "graphics/vulkan/renderers/renderer.h"

/*
* 
* RAII can be summarized as follows:
*    encapsulate each resource into a class, where
*       the constructor acquires the resource and establishes all class invariants or throws an exception if that cannot be done,
*       the destructor releases the resource and never throws exceptions;
*    always use the resource via an instance of a RAII-class that either
*       has automatic storage duration or temporary lifetime itself, or
*       has lifetime that is bounded by the lifetime of an automatic or temporary object
* 
* Move semantics make it possible to safely transfer resource ownership between objects, across scopes, and in and out of threads, while maintaining resource safety.
* Classes with open()/close(), lock()/unlock(), or init()/copyFrom()/destroy() member functions are typical examples of non-RAII classes
* 
* RAII does not apply to the management of the resources that are not acquired before use: 
* CPU time, cores, and cache capacity, entropy pool capacity, network bandwidth, electric power consumption, stack memory.
*/

namespace karamay_RHI
{

    class mesh {};

    class atmosphere {};

    class light {};

    class camera {};

    class scene {};


    class graph
    {
    public:

        template<typename device_object_t>
        device_object_t* create_persistent() noexcept
        {
            return nullptr;
        }

        template<typename device_object_t>
        std::shared_ptr<device_object_t> create_shared() noexcept
        {
            return nullptr;
        }

        template<typename device_object_t>
        std::unique_ptr<device_object_t> create_unique() noexcept
        {
            return nullptr;
        }

    };


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

            if (_invoked_devices.size() < 1)
            {
                return false;
            }
            
            auto _device = _invoked_devices.at(0);

            if (!_device->is_valid())
            {
                return false;
            }

            graph _graph;

            _graph.create_persistent<buffer>();


            buffer _vert_buf(*_device, 1024, VkBufferUsageFlagBits::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VkSharingMode::VK_SHARING_MODE_EXCLUSIVE);

            buffer_view _vert_buf(*_device, _vert_buf, VkFormat::VK_FORMAT_A1R5G5B5_UNORM_PACK16);


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
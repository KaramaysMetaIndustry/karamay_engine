#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "vulkan_object.h"

_KANAS_CORE_BEGIN

class physical_device;

class queue;

class device_memory;

class buffer;
class buffer_view;
class image;
class image_view;

class framebuffer;

class descriptor_pool;
class descriptor_set_layout;

class sampler;
class shader_module;
class pipeline_cache;
class pipeline_layout;
class render_pass;

class fence;
class semaphore;
class FEvent;

class command_pool;

class device final : public vulkan_object<VkDevice>
{
	friend class physical_device;

	bool allocate();

public:

	device(physical_device& InPhysicalDevice);

	device(const device&) = delete;
	device& operator=(const device&) = delete;

	virtual ~device() override;

	std::shared_ptr<queue> get_queue(std::uint32_t queue_family_index, std::uint32_t queue_index);

    std::shared_ptr<kanas::core::buffer> create_buffer(std::uint64_t size, buffer_usage_flags usage, std::shared_ptr<FConcurrentGuide> concurrent_guide);

    std::shared_ptr<kanas::core::buffer_view> create_buffer_view(std::shared_ptr<buffer> target, VkFormat format, VkDeviceSize offset, VkDeviceSize range);

    std::shared_ptr<kanas::core::fence> create_fence(bool IsDefaultSignaled);

    std::shared_ptr<kanas::core::semaphore> create_semaphore();

	physical_device& GetPhysicalDevice() const { return GPU; }

private:

	physical_device& GPU;

};

_KANAS_CORE_END


#endif

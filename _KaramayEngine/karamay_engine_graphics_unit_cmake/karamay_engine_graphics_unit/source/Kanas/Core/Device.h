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

	bool alllocate();

public:

	device(physical_device& InPhysicalDevice);

	device(const device&) = delete;
	device& operator=(const device&) = delete;

	virtual ~device() override;

	std::shared_ptr<queue> GetQueue(std::uint32_t InQueueFamilyIndex, std::uint32_t InQueueIndex);
	
	std::shared_ptr<buffer> CreateBuffer(std::uint64_t Size, buffer_usage_flags Usage, std::shared_ptr<FConcurrentGuide> ConcurrentGuide = nullptr);
	
	std::shared_ptr<buffer_view> Createbuffer_view(std::shared_ptr<buffer> Buffer, VkFormat Format, VkDeviceSize Offset, VkDeviceSize Range);
	
	std::shared_ptr<image> CreateImage();
	
	std::shared_ptr<image_view> CreateImageView(std::shared_ptr<image> Image, VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange);

	descriptor_pool* CreateDescriptorPool();

	std::shared_ptr<shader_module> CreateShaderModule(const std::vector<std::uint32_t>& ShaderCode);
	
	std::shared_ptr<pipeline_cache> Createpipeline_cache();
	
	std::shared_ptr<pipeline_layout> Createpipeline_layout();
	
	std::shared_ptr<render_pass> create_render_pass();

	command_pool* CreateCommandPool();

	std::shared_ptr<fence> CreateFence(bool IsDefaultSignaled = false);
	
	std::shared_ptr<semaphore> CreateSemaphore();
	
	std::shared_ptr<FEvent> CreateEvent();
	
	std::shared_ptr<sampler> CreateSampler();

	physical_device& GetPhysicalDevice() const { return GPU; }

private:

	physical_device& GPU;

};

_KANAS_CORE_END


#endif

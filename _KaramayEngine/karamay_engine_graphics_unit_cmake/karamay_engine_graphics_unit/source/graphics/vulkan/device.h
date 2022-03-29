#ifndef DEVICE_H
#define DEVICE_H
#include "vulkan_object.h"

class physical_device;
class queue;
class device_memory;
class buffer;
class buffer_view;
class image;
class image_view;
class sampler;
class acceleration_structure;
class descriptor_set;
class descriptor_set_layout;
class framebuffer;
class pipeline_cache;
class pipeline_layout;
class graphics_pipeline;
class mesh_pipeline;
class compute_pipeline;
class ray_tracing_pipeline;
class shader_module;
class render_pass;
class command_pool;
class descriptor_pool;
class renderer;

#define device_khr_func(func_name)\
PFN_##func_name##(vkGetDeviceProcAddr(_dev.handle(), #func_name))\

/*
* logical device, avatar of physical device
* 
*/
class device final : public vulkan_object<VkDevice>
{
public:

	device(physical_device& entity);

	device(const device&) = delete;
	device& operator=(const device&) = delete;

	~device();

private:

	physical_device& _entity;

	std::vector<std::vector<queue*>> _queues;

public:

	physical_device& entity() noexcept { return _entity; }

	/*
	* entity : the entity of logical device to be allocated
	*/
	bool allocate() noexcept;

	/*
	* 
	*/
	void deallocate() noexcept;

	/*
	*
	*/
	queue* invoke_queue(uint32 family_index, uint32 index) const noexcept;

	/*
	* 
	*/
	void get_descriptor_set_layout_support(VkDescriptorSetLayoutSupport& support) noexcept;

	/*
	* block, wait all queues finished, device to idle
	*/
	bool wait() const noexcept;

private:

	bool _should_exit = false;

	std::vector<renderer*> _renderers;

public:

	void run() noexcept;

	/* invoke a device object from device, and the object is not valid, you should allocate it by yourself. */
	template<typename device_object_t>
	std::shared_ptr<device_object_t> invoke() noexcept
	{
		return std::make_shared<device_object_t>(*this);
	}

};

#endif
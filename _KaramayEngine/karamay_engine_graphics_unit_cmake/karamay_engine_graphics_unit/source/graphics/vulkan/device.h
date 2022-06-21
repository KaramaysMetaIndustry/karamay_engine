#ifndef DEVICE_H
#define DEVICE_H
#include "vulkan_object.h"

class vk_physical_device;
class vk_queue;
class vk_device_memory;
class vk_buffer;
class vk_buffer_view;
class vk_image;
class vk_image_view;
class vk_sampler;
class vk_acceleration_structure;
class vk_descriptor_set;
class vk_descriptor_set_layout;
class vk_framebuffer;
class vk_shader_module;
class vk_pipeline_cache;
class vk_pipeline_layout;
class vk_graphics_pipeline;
class vk_mesh_pipeline;
class vk_compute_pipeline;
class vk_ray_tracing_pipeline;
class vk_render_pass;
class vk_command_pool;
class vk_descriptor_pool;
class vk_event;
class renderer;

#define device_khr_func(func_name)\
PFN_##func_name##(vkGetDeviceProcAddr(_dev.handle(), #func_name))\

/*
* logical device, avatar of physical device
* 
*/
class vk_device final : public vulkan_object<VkDevice>
{
public:

	vk_device(vk_physical_device& entity);

	vk_device(const vk_device&) = delete;
	vk_device& operator=(const vk_device&) = delete;

	~vk_device();

private:

	vk_physical_device& _entity;

	std::vector<std::vector<queue*>> _queues;

public:

	vk_physical_device& entity() noexcept { return _entity; }

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

	auto create_buffer(uint64 size, VkBufferUsageFlags usage, VkSharingMode sharing)
	{
		auto _buf = invoke<vk_buffer>();
		if (_buf && _buf->allocate(size, usage, sharing))
		{
			return _buf;
		}
		return nullptr;
	}

	auto create_buffer_view(std::shared_ptr<vk_buffer> buf, VkFormat format, uint32 offset, uint32 size)
	{
		auto _buf_view = invoke<vk_buffer_view>();
		if (_buf_view && _buf_view->allocate(buf, format, offset, size))
		{
			return _buf_view;
		}
		return nullptr;
	}


	auto create_event()
	{
		auto _event = invoke<vk_event>();
		if (_event && _event->allocate())
		{
			return _event;
		}
		return nullptr;
	}

private:

	/* invoke a device object from device, and the object is not valid, you should allocate it by yourself. */
	template<typename device_object_t>
	std::shared_ptr<device_object_t> invoke() noexcept
	{
		return std::make_shared<device_object_t>(*this);
	}

};

#endif
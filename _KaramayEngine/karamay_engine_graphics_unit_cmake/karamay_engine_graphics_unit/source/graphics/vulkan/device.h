#ifndef DEVICE_H
#define DEVICE_H
#include "vulkan_object.h"
#include "graphics/vulkan/structure/structure.h"

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
class vk_fence;
class vk_semaphore;
class vk_query_pool;
class renderer;

#define device_khr_func(func_name)\
PFN_##func_name##(vkGetDeviceProcAddr(_dev.handle(), #func_name))\

/*
* logical device, avatar of physical device
* 
*/
class vk_device final : public vulkan_object<VkDevice>
{

	vk_physical_device& _entity;

	std::vector<std::vector<vk_queue*>> _queues;

	bool _should_exit = false;

	std::vector<renderer*> _renderers;

public:

	vk_device(vk_physical_device& entity);

	vk_device(const vk_device&) = delete;
	vk_device& operator=(const vk_device&) = delete;

	~vk_device();

public:

	vk_physical_device& entity() noexcept { return _entity; }

	/*
	* entity : the entity of logical device to be allocated
	*/
	bool allocate() noexcept;

	void deallocate() noexcept;

	void get_descriptor_set_layout_support(VkDescriptorSetLayoutSupport& support) noexcept;

	bool wait() const noexcept;

	void run() noexcept;

public:

	vk_queue* invoke_queue(uint32 family_index, uint32 index) const noexcept;

	// about command buffers
	std::shared_ptr<vk_command_pool> create_command_pool(const vk_command_pool_parameters& parameters);
	
	// about pipelines
	std::shared_ptr<vk_graphics_pipeline> create_graphics_pipeline(const vk_graphics_pipeline_parameters& parameters);

	std::shared_ptr<vk_compute_pipeline> create_compute_pipeline(const vk_compute_pipeline_parameters& parameters);

	std::shared_ptr<vk_mesh_pipeline> create_mesh_pipeline(const vk_mesh_pipeline_parameters& parameters);

	std::shared_ptr<vk_ray_tracing_pipeline> create_ray_tracing_pipeline(const vk_ray_tracing_pipeline_parameters& parameters);

	// device memory
	std::shared_ptr<vk_device_memory> create_device_memory(const vk_device_memory_parameters& parameters);

	// about buffers
	std::shared_ptr<vk_buffer> create_buffer(const vk_buffer_parameters& parameters) noexcept;
	
	// about images
	std::shared_ptr<vk_image> create_image(const vk_image_parameters& parameters) noexcept;

	// about descriptor sets
	std::shared_ptr<vk_descriptor_pool> create_descriptor_pool(const vk_descriptor_pool_parameters& parameters);

	std::shared_ptr<vk_descriptor_set_layout> create_descriptor_set_layout(const vk_descriptor_set_layout_parameters& parameters);

	// about shader modules
	std::shared_ptr<vk_shader_module> create_shader_module(const vk_shader_module_parameters& parameters);

	// about samplers
	std::shared_ptr<vk_sampler> create_sampler(const vk_sampler_parameters& parameters);

	// about events
	std::shared_ptr<vk_event> create_event(const vk_event_parameters& parameters);

	// about fences
	std::shared_ptr<vk_fence> create_fence(const vk_fence_parameters& parameters);

	// about semaphores
	std::shared_ptr<vk_semaphore> create_semaphore(const vk_semaphore_parameters& parameters);

	// about query pool
	std::shared_ptr<vk_query_pool> create_query_pool(const vk_query_pool_parameters& parameters);

	// about render passes
	std::shared_ptr<vk_render_pass> create_render_pass(const vk_render_pass_parameters& parameters);

	// about framebuffer
	std::shared_ptr<vk_framebuffer> create_framebuffer(const vk_framebuffer_parameters& parameters);

private:

	/* invoke a device object from device, and the object is not valid, you should allocate it by yourself. */
	template<typename device_object_t, typename device_object_parameters_t>
	std::shared_ptr<device_object_t> invoke(const device_object_parameters_t& parameters) noexcept
	{
		auto _obj = std::make_shared<device_object_t>(*this);
		return _obj && _obj->allocate(parameters) ? _obj : nullptr;
	}

};

#endif
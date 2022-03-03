#ifndef DEVICE_H
#define DEVICE_H
#include "vulkan_object.h"

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
class command_pool;
class render_pass;

class device final : public vulkan_object<VkDevice>
{
public:

	device(VkDevice new_handle)
	{
		_handle = new_handle;
	}

public:

	std::shared_ptr<command_pool> create_command_pool();

	std::shared_ptr<buffer> create_buffer();

};

#endif
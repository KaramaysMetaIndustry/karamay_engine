#ifndef DEVICE_H
#define DEVICE_H
#include "vulkan_object.h"

class buffer;
class buffer_view;
class image;
class image_view;
class command_pool;
class device_memory;
class framebuffer;
class pipeline_cache;
class pipeline_layout;
class graphics_pipeline;
class mesh_pipeline;
class compute_pipeline;
class ray_tracing_pipeline;
class shader_module;
class render_pass;
class acceleration_structure;
class descriptor_set;
class descriptor_set_layout;
class sampler;

class device final : public vulkan_object<VkDevice>
{
public:

	device()
	{
		//vkCreateDevice()
	}

public:

	std::shared_ptr<command_pool> create_command_pool();

	std::shared_ptr<buffer> create_buffer();

};

#endif
#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "public/vulkan_core.h"
#include "public/stl.h"

class vk_semaphore;
class vk_command_buffer;

#define _DEF_PAR_STRUCT_CORE(CoreStructName)\
	const CoreStructName& core() const noexcept { return _create_info; }\
private:\
	CoreStructName _create_info;\

struct vk_submit_info
{
	std::vector<semaphore*> wait_semaphores;
	std::vector<semaphore*> signal_semaphores;
	std::vector<command_buffer*> command_buffers;
	VkPipelineStageFlags wait_dst_stage;
};

struct vk_device_memory_parameters
{
	friend class vk_device_memory;

	const VkMemoryRequirements& core() const noexcept { return _requirements; }

private:
	VkMemoryRequirements& _requirements;
};

struct vk_buffer_parameters
{
	friend class vk_buffer;

	vk_buffer_parameters()
	{
		VkBufferCreateInfo _CreateInfo
		{
			.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.size = size,
			.usage = usage,
			.sharingMode = sharing,
			.queueFamilyIndexCount = 0,
			.pQueueFamilyIndices = nullptr
		};
	}

	const VkBufferCreateInfo& core() const noexcept { return _create_info; }

private:
	VkBufferCreateInfo _create_info;
};

struct vk_buffer_view_parameters
{
	friend class vk_buffer_view;

	vk_buffer_view_parameters()
	{
		VkBufferViewCreateInfo _create_info
		{
			.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO,
			.pNext = nullptr,
			.flags = 0,
			.buffer = buf->handle(),
			.format = format,
			.offset = offset,
			.range = size,
		};
	}

	const VkBufferViewCreateInfo& core() const noexcept { return _create_info; }

private:
	VkBufferViewCreateInfo _create_info;
};

struct vk_image_parameters
{
	friend class vk_image;

	vk_image_parameters& image_type(VkImageType type)
	{
		_create_info.imageType = type;
		return *this;
	}

	vk_image_parameters() :
		_create_info{
			.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO,
			/*.imageType = type,
			.format = format,
			.extent = extent,
			.mipLevels = mipmaps,
			.arrayLayers = layers,
			.samples = samples,
			.tiling = tiling,
			.usage = usage,
			.sharingMode = sharing,
			.queueFamilyIndexCount = static_cast<uint32_t>(queue_family_indices.size()),
			.pQueueFamilyIndices = queue_family_indices.data(),
			.initialLayout = layout*/
	}
	{
	}

	const VkImageCreateInfo& core() const noexcept { return _create_info; }

private:
	
	VkImageCreateInfo _create_info;

};

struct vk_image_view_parameters
{
	friend class vk_image_view;

	vk_image_view_parameters() :
		_create_info
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.image = nullptr,
		.viewType = VkImageViewType::VK_IMAGE_VIEW_TYPE_1D,
		.format = VkFormat::VK_FORMAT_A1R5G5B5_UNORM_PACK16,
		.components{},
		.subresourceRange{}
	}
	{}

	_DEF_PAR_STRUCT_CORE(VkImageViewCreateInfo)
};

struct vk_descriptor_pool_parameters
{
	friend class vk_descriptor_pool;

	vk_descriptor_pool_parameters() :
		_create_info
	{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.flags{},
		.maxSets = 0,
		.poolSizeCount = 0,
		.pPoolSizes = nullptr
	}
	{}

	_DEF_PAR_STRUCT_CORE(VkDescriptorPoolCreateInfo)
};

struct vk_descriptor_set_layout_parameters
{
	friend class vk_descriptor_set_layout;

	vk_descriptor_set_layout_parameters()
	{}

	_DEF_PAR_STRUCT_CORE(VkDescriptorSetLayoutCreateInfo)
};

struct vk_shader_module_parameters
{
	friend class vk_shader_module;

	vk_shader_module_parameters()
	{}

	_DEF_PAR_STRUCT_CORE(VkShaderModuleCreateInfo)
};

struct vk_command_pool_parameters
{
	friend class vk_vk_command_pool;

	vk_command_pool_parameters()
	{}

	_DEF_PAR_STRUCT_CORE(VkCommandPoolCreateInfo)
};

struct vk_sampler_parameters
{
	friend class vk_sampler;

	vk_sampler_parameters()
	{}

	_DEF_PAR_STRUCT_CORE(VkSamplerCreateInfo)
};

struct vk_event_parameters
{
	friend class vk_event;

	vk_event_parameters()
	{}

	_DEF_PAR_STRUCT_CORE(VkEventCreateInfo)
};


struct vk_fence_parameters
{
	friend class vk_fence;

	vk_fence_parameters()
	{}

	_DEF_PAR_STRUCT_CORE(VkFenceCreateInfo)
};

struct vk_semaphore_parameters
{
	friend class vk_semaphore;

	vk_semaphore_parameters()
	{}

	_DEF_PAR_STRUCT_CORE(VkSemaphore)
};


struct vk_render_pass_parameters
{
	friend class vk_render_pass;

	vk_render_pass_parameters& set_attachments()
	{
	}

	vk_render_pass_parameters& set_subpasses()
	{

	}

	vk_render_pass_parameters& set_dependencies()
	{

	}

	vk_render_pass_parameters() :
		_create_info
	{
		.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO, 
		.pNext = nullptr,
		.flags = VkRenderPassCreateFlagBits::VK_RENDER_PASS_CREATE_FLAG_BITS_MAX_ENUM,
		.attachmentCount = 0,
		.pAttachments = nullptr,
		.subpassCount = 0,
		.pSubpasses = nullptr,
		.dependencyCount = 0,
		.pDependencies = nullptr
	}
	{}

	_DEF_PAR_STRUCT_CORE(VkRenderPassCreateInfo)
};


struct vk_graphics_pipeline_parameters
{
	friend class vk_graphics_pipeline;

	vk_graphics_pipeline_parameters()
	{}

	_DEF_PAR_STRUCT_CORE(VkGraphicsPipelineCreateInfo)
};

struct vk_compute_pipeline_parameters
{
	friend class vk_compute_pipeline;

	vk_compute_pipeline_parameters()
	{}

	_DEF_PAR_STRUCT_CORE(VkComputePipelineCreateInfo)
};

struct vk_mesh_pipeline_parameters
{
};

struct vk_ray_tracing_pipeline_parameters
{
	friend class vk_ray_tracing_pipeline;

	vk_ray_tracing_pipeline_parameters()
	{}

	_DEF_PAR_STRUCT_CORE(VkRayTracingPipelineCreateInfoKHR)
};

struct vk_query_pool_parameters
{
	friend class vk_query_pool;

	vk_query_pool_parameters()
	{}

	_DEF_PAR_STRUCT_CORE(VkQueryPoolCreateInfo)
};

struct vk_framebuffer_parameters
{
	friend class vk_framebuffer;

	vk_framebuffer_parameters()
	{}

	_DEF_PAR_STRUCT_CORE(VkFramebufferCreateInfo)
};

#endif
#ifndef STRUCTURE_H
#define STRUCTURE_H
#include "public/vulkan_core.h"
#include "public/stl.h"

class semaphore;
class command_buffer;

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

	VkImageViewCreateInfo _create_info
	{
		.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.image = img.handle(),
		.viewType = view_t,
		.format = format,
		.components = components,
		.subresourceRange = subresource_range
	};

	const VkImageViewCreateInfo& core() const noexcept { return _create_info; }

private:

	VkImageViewCreateInfo _create_info;
};

struct vk_descriptor_pool_parameters
{
	friend class vk_descriptor_pool;

	const VkDescriptorPoolCreateInfo& core() const noexcept { return _create_info; }

	VkDescriptorPoolCreateInfo _create_info
	{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.flags = 0,
		.maxSets = max,
		.poolSizeCount = count,
		.pPoolSizes = &pool_size,
	};

private:
	VkDescriptorPoolCreateInfo _create_info;
};

struct vk_descriptor_set_layout_parameters
{
	friend class vk_descriptor_set_layout;

	const VkDescriptorSetLayoutCreateInfo& core() const noexcept { return _create_info; }
private:
	VkDescriptorSetLayoutCreateInfo _create_info;
};

struct vk_shader_module_parameters
{
	friend class vk_shader_module;

	const VkShaderModuleCreateInfo& core() const noexcept { return _create_info; }

private:

	VkShaderModuleCreateInfo _create_info;
};

#endif
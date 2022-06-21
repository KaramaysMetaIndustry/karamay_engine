#include "buffer.h"
#include "device_memory.h"
#include "image.h"
#include "pooled_object/command_buffer.h"

vk_buffer::vk_buffer(device& dev)
	: device_object(dev)
{
}

vk_buffer::~vk_buffer()
{
	vkDestroyBuffer(_dev.handle(), _handle, nullptr);
}

bool vk_buffer::allocate(uint64 size, VkBufferUsageFlags usage, VkSharingMode sharing)
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

	if (vkCreateBuffer(_dev.handle(), &_CreateInfo, nullptr, &_handle) == VkResult::VK_SUCCESS)
	{
		// create device memory by buffer
		VkMemoryRequirements _requirements{};
		vkGetBufferMemoryRequirements(_dev.handle(), _handle, &_requirements);
		_memory = std::make_unique<vk_device_memory>(_dev, _requirements);

		// bind the memory and buffer
		if (vkBindBufferMemory(_dev.handle(), _handle, _memory->handle(), 0) == VkResult::VK_SUCCESS)
		{
			return true;
		}
	}

	return false;
}

void vk_buffer::copy_to(command_buffer& recorder, buffer& dst, const std::vector<VkBufferCopy>& regions)
{
	vkCmdCopyBuffer(recorder.handle(), _handle, dst.handle(), regions.size(), regions.data());
}

void vk_buffer::copy_to(command_buffer& recorder, image& dst, const std::vector<VkBufferImageCopy>& regions)
{
	vkCmdCopyBufferToImage(recorder.handle(), _handle, dst.handle(), dst.layout(), regions.size(), regions.data());
}

void vk_buffer::fill(command_buffer& recorder, uint64 offset, uint64 size, uint32 data)
{
	vkCmdFillBuffer(recorder.handle(), _handle, offset, size, data);
}

void vk_buffer::update(command_buffer& recorder, uint64 offset, uint64 size, void* data)
{
	vkCmdUpdateBuffer(recorder.handle(), _handle, offset, size, data);
}

vk_buffer_view::vk_buffer_view(device& dev) noexcept
	: device_object(dev)
{
}

bool vk_buffer_view::allocate(std::shared_ptr<vk_buffer> buf, VkFormat format, uint32 offset, uint32 size)
{
	if (buf)
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

		if (vkCreateBufferView(_dev.handle(), &_create_info, nullptr, &_handle) == VkResult::VK_SUCCESS)
		{
			_target = buf;
			return true;
		}
	}

	return false;
}

vk_buffer_view::~vk_buffer_view() noexcept
{
	vkDestroyBufferView(_dev.handle(), _handle, nullptr);
}

#include "buffer.h"
#include "device_memory.h"
#include "image.h"
#include "pooled_object/command_buffer.h"

vk_buffer::vk_buffer(vk_device& dev)
	: device_object(dev)
{
}

vk_buffer::~vk_buffer()
{
	vkDestroyBuffer(_dev.handle(), _handle, nullptr);
}

bool vk_buffer::allocate(const vk_buffer_parameters& parameters)
{
	if (vkCreateBuffer(_dev.handle(), &(parameters.core()), nullptr, &_handle) == VkResult::VK_SUCCESS)
	{
		// create device memory by buffer
		VkMemoryRequirements _requirements{};
		vkGetBufferMemoryRequirements(_dev.handle(), _handle, &_requirements);
		//_memory = std::make_unique<vk_device_memory>(_dev, _requirements);

		// bind the memory and buffer
		if (vkBindBufferMemory(_dev.handle(), _handle, _memory->handle(), 0) == VkResult::VK_SUCCESS)
		{
			return true;
		}
	}

	return false;
}

void vk_buffer::copy_to(vk_command_buffer& recorder, vk_buffer& dst, const std::vector<VkBufferCopy>& regions)
{
	vkCmdCopyBuffer(recorder.handle(), _handle, dst.handle(), regions.size(), regions.data());
}

void vk_buffer::copy_to(vk_command_buffer& recorder, vk_image& dst, const std::vector<VkBufferImageCopy>& regions)
{
	vkCmdCopyBufferToImage(recorder.handle(), _handle, dst.handle(), dst.layout(), regions.size(), regions.data());
}

void vk_buffer::fill(vk_command_buffer& recorder, uint64 offset, uint64 size, uint32 data)
{
	vkCmdFillBuffer(recorder.handle(), _handle, offset, size, data);
}

void vk_buffer::update(vk_command_buffer& recorder, uint64 offset, uint64 size, void* data)
{
	vkCmdUpdateBuffer(recorder.handle(), _handle, offset, size, data);
}

vk_buffer_view::vk_buffer_view(vk_device& dev, vk_buffer& buffer) noexcept
	: device_object(dev), _target(buffer)
{
}

vk_buffer_view::~vk_buffer_view()
{
}

bool vk_buffer_view::allocate(const vk_buffer_view_parameters& parameters)
{
	if (vkCreateBufferView(_dev.handle(), &(parameters.core()), nullptr, &_handle) == VkResult::VK_SUCCESS)
	{
		return true;
	}
	return false;
}

vk_buffer_view::~vk_buffer_view() noexcept
{
	vkDestroyBufferView(_dev.handle(), _handle, nullptr);
}

#include "buffer.h"
#include "device_memory.h"
#include "image.h"
#include "pooled_object/command_buffer.h"

buffer::buffer(device& dev, uint64 size, VkBufferUsageFlags usage, VkSharingMode sharing)
	: device_object(dev)
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

	auto _Result = vkCreateBuffer(_dev.handle(), &_CreateInfo, nullptr, &_handle);
	VkMemoryRequirements _requirements{};
	vkGetBufferMemoryRequirements(_dev.handle(), _handle, &_requirements);
	_memory = std::make_unique<device_memory>(_dev, _requirements);
}

buffer::~buffer() noexcept
{
	vkDestroyBuffer(_dev.handle(), _handle, nullptr);
}

void buffer::copy_to(command_buffer& recorder, buffer& dst, const std::vector<VkBufferCopy>& regions)
{
	vkCmdCopyBuffer(recorder.handle(), _handle, dst.handle(), regions.size(), regions.data());
}

void buffer::copy_to(command_buffer& recorder, image& dst, const std::vector<VkBufferImageCopy>& regions)
{
	vkCmdCopyBufferToImage(recorder.handle(), _handle, dst.handle(), dst.layout(), regions.size(), regions.data());
}

void buffer::fill(command_buffer& recorder, uint64 offset, uint64 size, uint32 data)
{
	vkCmdFillBuffer(recorder.handle(), _handle, offset, size, data);
}

void buffer::update(command_buffer& recorder, uint64 offset, uint64 size, void* data)
{
	vkCmdUpdateBuffer(recorder.handle(), _handle, offset, size, data);
}

buffer_view::buffer_view(device& dev, buffer& buf, VkFormat format) noexcept
	: device_object(dev), _target(buf)
{
	_Construct_nothrow(buf, format, 0, 0);
}

buffer_view::buffer_view(device& dev, buffer& buf, VkFormat format, uint32 offset, uint32 size) noexcept
	: device_object(dev), _target(buf)
{
	_Construct_nothrow(buf, format, offset, size);
}

buffer_view::~buffer_view() noexcept
{
	vkDestroyBufferView(_dev.handle(), _handle, nullptr);
}

void buffer_view::_Construct_nothrow(buffer& buf, VkFormat format, uint32 offset, uint32 size) noexcept
{
	VkBufferViewCreateInfo _create_info
	{
		.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO,
		.pNext = nullptr,
		.flags = 0,
		.buffer = buf.handle(),
		.format = format,
		.offset = offset,
		.range = size,
	};

	vkCreateBufferView(_dev.handle(), &_create_info, nullptr, &_handle);
}

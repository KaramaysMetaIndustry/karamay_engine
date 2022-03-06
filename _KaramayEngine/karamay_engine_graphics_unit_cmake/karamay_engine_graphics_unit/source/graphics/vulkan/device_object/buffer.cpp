#include "buffer.h"
#include "device_memory.h"
#include "pooled_object/command_buffer.h"

buffer::buffer(device& dev) : device_object(dev)
{
}

buffer::~buffer()
{
	deallocate();
}

bool buffer::allocate(uint64 size, VkBufferUsageFlagBits usage_flags, VkSharingMode sharing_mode)
{
	if (!_memory->allocate(size, 0))
	{
		return false;
	}

	VkBufferCreateInfo _create_info;
	_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	_create_info.usage = usage_flags;
	_create_info.size = size;
	_create_info.sharingMode = sharing_mode;

	auto _ret = vkCreateBuffer(_device.handle(), &_create_info, nullptr, &_handle);

	if (_ret != VkResult::VK_SUCCESS)
	{
		return false;
	}
	return true;
}

void buffer::deallocate()
{
	vkDestroyBuffer(_device.handle(), _handle, nullptr);
	_handle = nullptr;
}

void buffer::copy_to(command_buffer* recorder, buffer* dst, const std::vector<VkBufferCopy>& regions)
{
	vkCmdCopyBuffer({}, _handle, dst->handle(), regions.size(), regions.data());
}

void buffer::copy_to(command_buffer* recorder, image* dst)
{
	//vkCmdCopyBuffer();
}

void buffer::fill(command_buffer* recorder, uint64 offset, uint64 size, uint32 data)
{
	vkCmdFillBuffer(recorder->handle(), _handle, offset, size, data);
}

void buffer::update(command_buffer* recorder, uint64 offset, uint64 size, void* data)
{
	vkCmdUpdateBuffer(recorder->handle(), _handle, offset, size, data);
}

#include "buffer.h"
#include "device_memory.h"
#include "image.h"
#include "pooled_object/command_buffer.h"

buffer::buffer(device& dev) : device_object(dev)
{
}

buffer::~buffer()
{
	deallocate();
}

bool buffer::allocate(uint64 size, VkBufferUsageFlags usage_flags, VkSharingMode sharing_mode) noexcept
{
	if (size == 0)
	{
		return false;
	}

	deallocate();

	VkBufferCreateInfo _create_info{};
	_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	_create_info.usage = usage_flags;
	_create_info.size = size;
	_create_info.sharingMode = sharing_mode;

	auto _ret = vkCreateBuffer(_device.handle(), &_create_info, nullptr, &_handle);
	if (_ret != VkResult::VK_SUCCESS)
	{
		return false;
	}

	VkMemoryRequirements _requirements;
	vkGetBufferMemoryRequirements(_device.handle(), _handle, &_requirements);
	
	auto _memory = _device.invoke<device_memory>();
	if (!_memory || !_memory->allocate(_requirements))
	{
		return false;
	}

	// lazy cache
	this->_memory = _memory;
	this->_sharing_mode = sharing_mode;
	this->_usage_flags = usage_flags;
	return true;
}

void buffer::deallocate() noexcept
{
	if (_handle)
	{
		vkDestroyBuffer(_device.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

void buffer::copy_to(command_buffer* recorder, buffer* dst, const std::vector<VkBufferCopy>& regions)
{
	vkCmdCopyBuffer(recorder->handle(), _handle, dst->handle(), regions.size(), regions.data());
}

void buffer::copy_to(command_buffer* recorder, image* dst, const std::vector<VkBufferImageCopy>& regions)
{
	vkCmdCopyBufferToImage(recorder->handle(), _handle, dst->handle(), dst->layout(), regions.size(), regions.data());
}

void buffer::fill(command_buffer* recorder, uint64 offset, uint64 size, uint32 data)
{
	vkCmdFillBuffer(recorder->handle(), _handle, offset, size, data);
}

void buffer::update(command_buffer* recorder, uint64 offset, uint64 size, void* data)
{
	vkCmdUpdateBuffer(recorder->handle(), _handle, offset, size, data);
}



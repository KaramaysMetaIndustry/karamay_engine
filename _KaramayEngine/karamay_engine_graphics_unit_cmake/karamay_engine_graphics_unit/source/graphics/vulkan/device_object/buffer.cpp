#include "buffer.h"

buffer::buffer(device& dev) : device_object(dev)
{
}

bool buffer::allocate(uint64 size, VkBufferUsageFlagBits usage_flags, VkSharingMode sharing_mode)
{
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

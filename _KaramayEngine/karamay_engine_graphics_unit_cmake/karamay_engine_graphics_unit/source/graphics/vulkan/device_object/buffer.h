#ifndef BUFFER_H
#define BUFFER_H
#include "device_object.h"

class command_buffer;
class image;

class buffer final : public device_object<VkBuffer>
{
public:
	buffer(device* dev) : device_object(dev) {}

	bool allocate(uint64 size)
	{
		VkBufferCreateInfo _create_info;
		_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		_create_info.usage = VkBufferUsageFlagBits::VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
		_create_info.size = size;
		_create_info.sharingMode = VkSharingMode::VK_SHARING_MODE_CONCURRENT;
		auto _ret = vkCreateBuffer(_device->handle(), &_create_info, nullptr, &_handle);

		return true;
	}

	void deallocate()
	{
		vkDestroyBuffer(_device->handle(), _handle, nullptr);
	}

public:

	void copy_to(command_buffer* recorder, buffer* dst, const std::vector<VkBufferCopy>& regions)
	{
		vkCmdCopyBuffer({}, _handle, dst->handle(), regions.size(), regions.data());
	}

	void copy_to(command_buffer* recorder, image* dst)
	{

	}

	void copy_from(command_buffer* recorder, buffer* src);

	void copy_from(command_buffer* recorder, image* src);

};

#endif
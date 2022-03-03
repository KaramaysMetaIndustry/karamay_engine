#ifndef DEVICE_MEMORY_H
#define DEVICE_MEMORY_H
#include "device_object.h"

class device_memory final : public device_object<VkDeviceMemory>
{
public:

	bool allocate(uint64 size, uint32 memory_type_index)
	{
		VkMemoryAllocateInfo _allocate_info;
		_allocate_info.allocationSize = size;
		_allocate_info.memoryTypeIndex = memory_type_index;
		vkAllocateMemory(_device->handle(), &_allocate_info, nullptr, &_handle);
		return true;
	}

	void deallocate()
	{
		vkFreeMemory(_device->handle(), _handle, nullptr);
	}

};

#endif
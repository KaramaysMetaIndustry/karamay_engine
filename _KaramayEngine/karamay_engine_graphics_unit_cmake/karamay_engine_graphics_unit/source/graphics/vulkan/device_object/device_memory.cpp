#include "device_memory.h"

device_memory::device_memory(device& dev) : device_object(dev)
{
}

device_memory::~device_memory()
{
	deallocate();
}

bool device_memory::allocate(uint64 size, uint32 memory_type_index) noexcept
{
	VkMemoryAllocateInfo _allocate_info;
	_allocate_info.allocationSize = size;
	_allocate_info.memoryTypeIndex = memory_type_index;
	vkAllocateMemory(_device.handle(), &_allocate_info, nullptr, &_handle);
	return true;
}

void device_memory::deallocate() noexcept
{
	if (_handle)
	{
		vkFreeMemory(_device.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

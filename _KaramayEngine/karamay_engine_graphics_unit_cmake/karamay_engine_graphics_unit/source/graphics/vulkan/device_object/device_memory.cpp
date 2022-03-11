#include "device_memory.h"
#include "graphics/vulkan/physical_device.h"

device_memory::~device_memory()
{
	_Deallocate();
}

void device_memory::_Deallocate() noexcept
{
	if (_Handle)
	{
		vkFreeMemory(_Device.handle(), _Handle, nullptr);
		_Handle = nullptr;
	}
}

void device_memory::exec_handler(uint64 offset, uint64 size, const device_memory_handler& handler, VkMemoryMapFlags flags) const noexcept
{
	void* _Data = nullptr;
	VkResult _Result = vkMapMemory(_Device.handle(), _Handle, offset, size, flags, &_Data);
	if (_Result != VkResult::VK_SUCCESS || !_Data) return;
	handler(size, _Data);
	vkUnmapMemory(_Device.handle(), _Handle);
}

void device_memory::exec_handler(const device_memory_handler& handler, VkMemoryMapFlags flags) noexcept
{
	exec_handler(0, _Size, handler, flags);
}

uint32 device_memory::_Find_memory_type(uint32 typeFilter, VkMemoryPropertyFlags properties) noexcept
{
	VkPhysicalDeviceMemoryProperties memProperties;
	_Device.entity().get_memory_properties(memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}
}

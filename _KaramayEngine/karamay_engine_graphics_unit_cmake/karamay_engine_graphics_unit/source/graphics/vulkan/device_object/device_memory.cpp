#include "device_memory.h"
#include "graphics/vulkan/physical_device.h"

vk_device_memory::~vk_device_memory()
{
	_deallocate();
}

void vk_device_memory::_deallocate() noexcept
{
	if (_handle)
	{
		vkFreeMemory(_dev.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

void vk_device_memory::exec_handler(uint64 offset, uint64 size, const device_memory_handler& handler, VkMemoryMapFlags flags) const noexcept
{
	void* _Data = nullptr;
	VkResult _Result = vkMapMemory(_dev.handle(), _handle, offset, size, flags, &_Data);
	if (_Result != VkResult::VK_SUCCESS || !_Data) return;
	handler(size, _Data);
	vkUnmapMemory(_dev.handle(), _handle);
}

void vk_device_memory::exec_handler(const device_memory_handler& handler, VkMemoryMapFlags flags) noexcept
{
	exec_handler(0, _size, handler, flags);
}

uint32 vk_device_memory::_find_memory_type(uint32 typeFilter, VkMemoryPropertyFlags properties) noexcept
{
	VkPhysicalDeviceMemoryProperties memProperties;
	_dev.entity().get_memory_properties(memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}
}

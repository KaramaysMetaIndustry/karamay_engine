#include "device_memory.h"
#include "graphics/vulkan/physical_device.h"

device_memory::device_memory(device& dev) : device_object(dev)
{
}

device_memory::~device_memory()
{
	deallocate();
}

bool device_memory::allocate(uint64 size, uint32 memory_type_index) noexcept
{
	VkMemoryAllocateInfo _allocate_info{};
	_allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	_allocate_info.allocationSize = size;
	_allocate_info.memoryTypeIndex = memory_type_index;
	VkResult _result = vkAllocateMemory(_device.handle(), &_allocate_info, nullptr, &_handle);
	if (_result != VkResult::VK_SUCCESS)
	{
		return false;
	}
	return true;
}

bool device_memory::allocate(const VkMemoryRequirements& requirements) noexcept
{
	VkMemoryAllocateInfo _allocate_info{};
	_allocate_info.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	_allocate_info.allocationSize = requirements.size;
	_allocate_info.memoryTypeIndex = _find_memory_type(
		requirements.memoryTypeBits, 
		VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
	);

	VkResult _result = vkAllocateMemory(_device.handle(), &_allocate_info, nullptr, &_handle);
	if (_result != VkResult::VK_SUCCESS)
	{
		return false;
	}
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

void device_memory::execute_handler(uint64 offset, uint64 size, VkMemoryMapFlags flags, const std::function<void(uint64 size, void* data)>& handler) noexcept
{
	void* _data = nullptr;
	VkResult _result = vkMapMemory(_device.handle(), _handle, offset, size, flags, &_data);
	if (_result != VkResult::VK_SUCCESS || !_data)
	{
		return;
	}
	handler(size, _data);
	vkUnmapMemory(_device.handle(), _handle);
}

uint32 device_memory::_find_memory_type(uint32 typeFilter, VkMemoryPropertyFlags properties) noexcept
{
	VkPhysicalDeviceMemoryProperties memProperties;
	_device.entity->get_memory_properties(memProperties);

	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++)
	{
		if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties)
		{
			return i;
		}
	}
}

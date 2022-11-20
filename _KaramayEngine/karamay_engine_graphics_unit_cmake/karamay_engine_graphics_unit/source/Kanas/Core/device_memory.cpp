#include "device_memory.h"
#include "device.h"
#include "physical_device.h"

kanas::core::device_memory::device_memory(device& owner) :
	device_object(owner)
{
}

kanas::core::device_memory::~device_memory()
{
	if (IsValid())
	{
		vkFreeMemory(get_device().get_handle(), get_handle(), nullptr);
		
		reset_handle();
	}
}

bool kanas::core::device_memory::alllocate(VkDeviceSize InAllocSize, std::uint32_t InMemTypeIndex)
{
	VkMemoryalllocateInfo MemoryalllocateInfo{};
	MemoryalllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_alllocate_INFO;
	MemoryalllocateInfo.pNext = nullptr;
	MemoryalllocateInfo.allocationSize = InAllocSize;
	MemoryalllocateInfo.memoryTypeIndex = InMemTypeIndex;

	const VkResult _Result = vkalllocateMemory(get_device().get_handle(), &MemoryalllocateInfo, nullptr, &handle);
	
	if (_Result == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

void kanas::core::device_memory::HandleMemory(std::uint64_t InOffset, std::uint64_t InSize, const device_memoryHandler& InHandler, VkMemoryMapFlags InFlags)
{
	void* Data = nullptr;

	const VkResult _Result = vkMapMemory(get_device().get_handle(), get_handle(), InOffset, InSize, InFlags, &Data);
	
	if (_Result != VkResult::VK_SUCCESS || !Data)
	{
		return;
	}

	InHandler(InSize, Data);

	vkUnmapMemory(get_device().get_handle(), get_handle());
}

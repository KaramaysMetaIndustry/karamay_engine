#include "DeviceMemory.h"
#include "Device.h"
#include "PhysicalDevice.h"

Kanas::Core::FDeviceMemory::FDeviceMemory(FDevice& InDevice) :
	FDeviceObject(InDevice)
{
}

Kanas::Core::FDeviceMemory::~FDeviceMemory()
{
	if (IsValid())
	{
		vkFreeMemory(GetDevice().GetHandle(), GetHandle(), nullptr);
		
		ResetHandle();
	}
}

bool Kanas::Core::FDeviceMemory::Allocate(VkDeviceSize InAllocSize, uint32 InMemTypeIndex)
{
	VkMemoryAllocateInfo MemoryAllocateInfo{};
	MemoryAllocateInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	MemoryAllocateInfo.pNext = nullptr;
	MemoryAllocateInfo.allocationSize = InAllocSize;
	MemoryAllocateInfo.memoryTypeIndex = InMemTypeIndex;

	const VkResult _Result = vkAllocateMemory(GetDevice().GetHandle(), &MemoryAllocateInfo, nullptr, &_Handle);
	
	if (_Result == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

void Kanas::Core::FDeviceMemory::HandleMemory(uint64 InOffset, uint64 InSize, const DeviceMemoryHandler& InHandler, VkMemoryMapFlags InFlags)
{
	void* Data = nullptr;

	const VkResult _Result = vkMapMemory(GetDevice().GetHandle(), GetHandle(), InOffset, InSize, InFlags, &Data);
	
	if (_Result != VkResult::VK_SUCCESS || !Data)
	{
		return;
	}

	InHandler(InSize, Data);

	vkUnmapMemory(GetDevice().GetHandle(), GetHandle());
}

#include "DeviceMemory.h"
#include "Device.h"

Kanas::Core::DeviceMemory::DeviceMemory(Device& InDevice) :
	DeviceObject(InDevice)
{
}

Kanas::Core::DeviceMemory::~DeviceMemory()
{
	if (IsValid())
	{
		vkFreeMemory(GetDevice().GetHandle(), GetHandle(), nullptr);
		
		ResetHandle();
	}
}

bool Kanas::Core::DeviceMemory::Allocate()
{

	VkMemoryAllocateInfo _AllocateInfo;

	const VkResult _Result = vkAllocateMemory(GetDevice().GetHandle(), &_AllocateInfo, nullptr, &_Handle);
	
	if (_Result == VkResult::VK_SUCCESS && _Handle)
	{
		return true;
	}

	return false;
}

void Kanas::Core::DeviceMemory::HandleMemory(uint64 InOffset, uint64 InSize, const DeviceMemoryHandler& InHandler, VkMemoryMapFlags InFlags)
{
	void* _Data = nullptr;

	const VkResult _Result = vkMapMemory(GetDevice().GetHandle(), _Handle, InOffset, InSize, InFlags, &_Data);
	
	if (_Result != VkResult::VK_SUCCESS || !_Data)
	{
		return;
	}

	InHandler(InSize, _Data);

	vkUnmapMemory(GetDevice().GetHandle(), _Handle);
}

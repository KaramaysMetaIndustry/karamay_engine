#include "Queue.h"
#include "Device.h"
#include "Fence.h"

Kanas::Core::Queue::Queue(Device& InDevice) :
	DeviceObject(InDevice)
{
}

Kanas::Core::Queue::~Queue()
{
}

bool Kanas::Core::Queue::Allocate(uint32 InQueueFamilyIndex, uint32 InQueueIndex)
{
	vkGetDeviceQueue(GetDevice().GetHandle(), InQueueFamilyIndex, InQueueIndex, &_Handle);
	return true;
}

Kanas::Core::QueuePool* Kanas::Core::Queue::GetOwner() const
{
	return Owner;
}

void Kanas::Core::Queue::BindSpare(const VkBindSparseInfo& InBindSparseInfo, Fence* InFence)
{
	VkResult Result = vkQueueBindSparse(GetHandle(), 1, &InBindSparseInfo, InFence->GetHandle());
}

void Kanas::Core::Queue::WaitIdle()
{
	VkResult Result = vkQueueWaitIdle(GetHandle());
}

void Kanas::Core::Queue::Submit(const VkSubmitInfo& InSubmitInfo, Fence* InFence)
{
	VkFence FenceHandle = VK_NULL_HANDLE;
	
	if (InFence)
	{
		FenceHandle = InFence->GetHandle();
	}

	VkResult Result = vkQueueSubmit(GetHandle(), 1, &InSubmitInfo, FenceHandle);
}

void Kanas::Core::Queue::PresetKHR(const VkPresentInfoKHR& InPresentInfo)
{
	VkResult Result = vkQueuePresentKHR(GetHandle(), &InPresentInfo);
}
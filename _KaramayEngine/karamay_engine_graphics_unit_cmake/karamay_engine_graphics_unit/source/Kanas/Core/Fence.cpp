#include "Fence.h"
#include "Device.h"

Kanas::Core::Fence::Fence(Device& InDevice) :
	DeviceObject(InDevice)
{
}

Kanas::Core::Fence::~Fence()
{
	if (IsValid())
	{
		vkDestroyFence(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

bool Kanas::Core::Fence::Allocate(bool IsSignaled)
{
	VkFenceCreateInfo FenceCreateInfo;
	FenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	FenceCreateInfo.pNext = nullptr;
	FenceCreateInfo.flags = {};

	VkResult Result = vkCreateFence(GetDevice().GetHandle(), &FenceCreateInfo, nullptr, &_Handle);
	
	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}
	
	return false;
}

bool Kanas::Core::Fence::Wait(uint64 InTimeoutInNs)
{
	// VK_SUCCESS VK_TIMEOUT VK_ERROR_DEVICE_LOST
	const VkResult Result = vkWaitForFences(GetDevice().GetHandle(), 1, &_Handle, true, InTimeoutInNs);
	return Result == VkResult::VK_SUCCESS;
}

VkResult Kanas::Core::Fence::GetStatus()
{
	return vkGetFenceStatus(GetDevice().GetHandle(), GetHandle());
}

void Kanas::Core::Fence::Reset()
{
	vkResetFences(GetDevice().GetHandle(), 1, &_Handle);
}

bool Kanas::Core::Fence::IsSignaled()
{
	// VK_SUCCESS VK_NOT_READY VK_ERROR_DEVICE_LOST
	return GetStatus() == VkResult::VK_SUCCESS;
}

void Kanas::Core::TransientFenceGroup::Reset()
{
}

bool Kanas::Core::TransientFenceGroup::Wait(bool InWaitAll, uint64 InTimeoutInMs)
{
	if (Fences.size() > 0)
	{
		Device& TheDevice = Fences[0]->GetDevice();

		std::vector<VkFence> FenceHandles;

		const VkResult Result = vkWaitForFences(TheDevice.GetHandle(), FenceHandles.size(), FenceHandles.data(), InWaitAll, InTimeoutInMs);
		return Result == VkResult::VK_SUCCESS;
	}
	return false;
}


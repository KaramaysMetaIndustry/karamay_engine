#include "Fence.h"
#include "Device.h"

Kanas::Core::FFence::FFence(FDevice& InDevice) :
	FDeviceObject(InDevice)
{
}

Kanas::Core::FFence::~FFence()
{
	if (IsValid())
	{
		vkDestroyFence(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

bool Kanas::Core::FFence::Allocate(bool IsSignaled)
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

bool Kanas::Core::FFence::Wait(uint64 InTimeoutInNs)
{
	// VK_SUCCESS VK_TIMEOUT VK_ERROR_DEVICE_LOST
	const VkResult Result = vkWaitForFences(GetDevice().GetHandle(), 1, &_Handle, true, InTimeoutInNs);
	return Result == VkResult::VK_SUCCESS;
}

VkResult Kanas::Core::FFence::GetStatus()
{
	return vkGetFenceStatus(GetDevice().GetHandle(), GetHandle());
}

void Kanas::Core::FFence::Reset()
{
	vkResetFences(GetDevice().GetHandle(), 1, &_Handle);
}

bool Kanas::Core::FFence::IsSignaled()
{
	// VK_SUCCESS VK_NOT_READY VK_ERROR_DEVICE_LOST
	return GetStatus() == VkResult::VK_SUCCESS;
}

void Kanas::Core::FTransientFenceGroup::Reset()
{
}

bool Kanas::Core::FTransientFenceGroup::Wait(bool InWaitAll, uint64 InTimeoutInMs)
{
	if (Fences.size() > 0)
	{
		FDevice& TheDevice = Fences[0]->GetDevice();

		std::vector<VkFence> FenceHandles;

		const VkResult Result = vkWaitForFences(TheDevice.GetHandle(), FenceHandles.size(), FenceHandles.data(), InWaitAll, InTimeoutInMs);
		return Result == VkResult::VK_SUCCESS;
	}
	return false;
}


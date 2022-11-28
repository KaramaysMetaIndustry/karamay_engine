#include "fence.h"
#include "device.h"

kanas::core::fence::fence(device& owner) :
	device_object(owner)
{
}

kanas::core::fence::~fence()
{
	if (IsValid())
	{
		vkDestroyFence(get_device().get_handle(), get_handle(), nullptr);

		reset_handle();
	}
}

bool kanas::core::fence::allocate(bool IsSignaled)
{
	VkFenceCreateInfo FenceCreateInfo;
	FenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	FenceCreateInfo.pNext = nullptr;
	FenceCreateInfo.flags = {};

	VkResult Result = vkCreateFence(get_device().get_handle(), &FenceCreateInfo, nullptr, &handle);
	
	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}
	
	return false;
}

bool kanas::core::fence::Wait(std::uint64_t InTimeoutInNs)
{
	// VK_SUCCESS VK_TIMEOUT VK_ERROR_DEVICE_LOST
	const VkResult Result = vkWaitForFences(get_device().get_handle(), 1, &handle, true, InTimeoutInNs);
	return Result == VkResult::VK_SUCCESS;
}

VkResult kanas::core::fence::GetStatus()
{
	return vkGetFenceStatus(get_device().get_handle(), get_handle());
}

void kanas::core::fence::Reset()
{
	vkResetFences(get_device().get_handle(), 1, &handle);
}

bool kanas::core::fence::IsSignaled()
{
	// VK_SUCCESS VK_NOT_READY VK_ERROR_DEVICE_LOST
	return GetStatus() == VkResult::VK_SUCCESS;
}

void kanas::core::FTransientFenceGroup::Reset()
{
}

bool kanas::core::FTransientFenceGroup::Wait(bool InWaitAll, std::uint64_t InTimeoutInMs)
{
	if (Fences.size() > 0)
	{
		device& TheDevice = Fences[0]->get_device();

		std::vector<VkFence> FenceHandles;

		const VkResult Result = vkWaitForFences(TheDevice.get_handle(), FenceHandles.size(), FenceHandles.data(), InWaitAll, InTimeoutInMs);
		return Result == VkResult::VK_SUCCESS;
	}
	return false;
}


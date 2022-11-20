#include "semaphore.h"
#include "device.h"

kanas::core::semaphore::semaphore(device& owner) :
	deviceObject(owner)
{
}

kanas::core::semaphore::~semaphore()
{
	if (IsValid())
	{
		vkDestroySemaphore(get_device().get_handle(), get_handle(), nullptr);

		reset_handle();
	}
}

bool kanas::core::semaphore::alllocate(VkSemaphoreType InType, std::uint64_t InInitalValue)
{
	VkSemaphoreTypeCreateInfo SemaphoreTypeCreateInfo{};
	SemaphoreTypeCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO;
	SemaphoreTypeCreateInfo.pNext = nullptr;
	SemaphoreTypeCreateInfo.semaphoreType = InType;
	SemaphoreTypeCreateInfo.initialValue = InInitalValue;

	VkSemaphoreCreateInfo SemaphoreCreateInfo{};
	SemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	SemaphoreCreateInfo.pNext = &SemaphoreTypeCreateInfo;
	SemaphoreCreateInfo.flags = {};

	VkResult Result = vkCreateSemaphore(get_device().get_handle(), &SemaphoreCreateInfo, nullptr, &handle);

	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

VkResult kanas::core::semaphore::Wait(std::uint64_t InValue, std::uint64_t InTimeout)
{
	VkSemaphore SemaphoreHandles[] = { get_handle() };

	VkSemaphoreWaitInfo SemaphoreWaitInfo;
	SemaphoreWaitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO;
	SemaphoreWaitInfo.pNext = nullptr;
	SemaphoreWaitInfo.flags = {};
	SemaphoreWaitInfo.semaphoreCount = 1;
	SemaphoreWaitInfo.pSemaphores = SemaphoreHandles;
	SemaphoreWaitInfo.pValues = &InValue;

	return vkWaitSemaphores(get_device().get_handle(), &SemaphoreWaitInfo, InTimeout);
}

VkResult kanas::core::semaphore::Signal(std::uint64_t InValue)
{
	VkSemaphoreSignalInfo SemaphoreSignalInfo;
	SemaphoreSignalInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO;
	SemaphoreSignalInfo.pNext = nullptr;
	SemaphoreSignalInfo.semaphore = get_handle();
	SemaphoreSignalInfo.value = InValue;

	return vkSignalSemaphore(get_device().get_handle(), &SemaphoreSignalInfo);
}

std::uint64_t kanas::core::semaphore::GetCounterValue()
{
	std::uint64_t Value = 0;
	vkGetSemaphoreCounterValue(get_device().get_handle(), get_handle(), &Value);
	return Value;
}

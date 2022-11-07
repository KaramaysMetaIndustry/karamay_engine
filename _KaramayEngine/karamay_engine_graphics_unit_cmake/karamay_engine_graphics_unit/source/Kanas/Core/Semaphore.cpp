#include "Semaphore.h"
#include "Device.h"

Kanas::Core::Semaphore::Semaphore(Device& InDevice) :
	DeviceObject(InDevice)
{
}

Kanas::Core::Semaphore::~Semaphore()
{
	if (IsValid())
	{
		vkDestroySemaphore(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

bool Kanas::Core::Semaphore::Allocate(VkSemaphoreType InType, uint64 InInitalValue)
{
	VkSemaphoreTypeCreateInfo SemaphoreTypeCreateInfo;
	SemaphoreTypeCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_TYPE_CREATE_INFO;
	SemaphoreTypeCreateInfo.pNext = nullptr;
	SemaphoreTypeCreateInfo.semaphoreType = InType;
	SemaphoreTypeCreateInfo.initialValue = InInitalValue;

	VkSemaphoreCreateInfo SemaphoreCreateInfo;
	SemaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	SemaphoreCreateInfo.pNext = &SemaphoreTypeCreateInfo;
	SemaphoreCreateInfo.flags = {};

	VkResult Result = vkCreateSemaphore(GetDevice().GetHandle(), &SemaphoreCreateInfo, nullptr, &_Handle);

	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

VkResult Kanas::Core::Semaphore::Wait(uint64 InValue, uint64 InTimeout)
{
	VkSemaphore SemaphoreHandles[] = { GetHandle() };

	VkSemaphoreWaitInfo SemaphoreWaitInfo;
	SemaphoreWaitInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_WAIT_INFO;
	SemaphoreWaitInfo.pNext = nullptr;
	SemaphoreWaitInfo.flags = {};
	SemaphoreWaitInfo.semaphoreCount = 1;
	SemaphoreWaitInfo.pSemaphores = SemaphoreHandles;
	SemaphoreWaitInfo.pValues = &InValue;

	return vkWaitSemaphores(GetDevice().GetHandle(), &SemaphoreWaitInfo, InTimeout);
}

VkResult Kanas::Core::Semaphore::Signal(uint64 InValue)
{
	VkSemaphoreSignalInfo SemaphoreSignalInfo;
	SemaphoreSignalInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_SIGNAL_INFO;
	SemaphoreSignalInfo.pNext = nullptr;
	SemaphoreSignalInfo.semaphore = GetHandle();
	SemaphoreSignalInfo.value = InValue;

	return vkSignalSemaphore(GetDevice().GetHandle(), &SemaphoreSignalInfo);
}

uint64 Kanas::Core::Semaphore::GetCounterValue()
{
	uint64 Value = 0;
	vkGetSemaphoreCounterValue(GetDevice().GetHandle(), GetHandle(), &Value);
	return Value;
}

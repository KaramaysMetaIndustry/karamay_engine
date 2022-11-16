#include "DeferredOperation.h"
#include "Device.h"


bool Kanas::Core::FDeferredOperation::Allocate()
{
	const VkResult DeferredOperationCreationResult = vkCreateDeferredOperationKHR(GetDevice().GetHandle(), nullptr, &_Handle);

	if (DeferredOperationCreationResult == VK_SUCCESS)
	{
		return true;
	}

	return false;
}

Kanas::Core::FDeferredOperation::FDeferredOperation(FDevice& Device) :
	FDeviceObject(Device)
{
}

Kanas::Core::FDeferredOperation::~FDeferredOperation()
{
	if (IsValid())
	{
		vkDestroyDeferredOperationKHR(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

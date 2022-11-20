#include "deferred_operation.h"
#include "device.h"

bool kanas::core::deferred_operation::alllocate()
{
	const VkResult DeferredOperationCreationResult = vkCreateDeferredOperationKHR(get_device().get_handle(), nullptr, &handle);

	if (DeferredOperationCreationResult == VK_SUCCESS)
	{
		return true;
	}

	return false;
}

kanas::core::deferred_operation::deferred_operation(device& Device) :
	device_object(Device)
{
}

kanas::core::deferred_operation::~deferred_operation()
{
	if (IsValid())
	{
		vkDestroyDeferredOperationKHR(get_device().get_handle(), get_handle(), nullptr);

		reset_handle();
	}
}

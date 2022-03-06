#include "deferred_operation.h"

deferred_operation::deferred_operation(device& dev) : device_object(dev)
{
}

deferred_operation::~deferred_operation()
{
	deallocate();
}

bool deferred_operation::allocate() noexcept
{
	device_khr_func(vkCreateDeferredOperationKHR)(_device.handle(), nullptr, &_handle);
	return true;
}

void deferred_operation::deallocate() noexcept
{
	device_khr_func(vkDestroyDeferredOperationKHR)(_device.handle(), _handle, nullptr);
	_handle = nullptr;
}

bool deferred_operation::join() noexcept
{
	device_khr_func(vkDeferredOperationJoinKHR)(_device.handle(), _handle);
	return true;
}

uint32 deferred_operation::get_max_concurrency() const noexcept
{
	return device_khr_func(vkGetDeferredOperationMaxConcurrencyKHR)(_device.handle(), _handle);
}

bool deferred_operation::get_result() const noexcept
{
	device_khr_func(vkGetDeferredOperationResultKHR)(_device.handle(), _handle);
	return true;
}

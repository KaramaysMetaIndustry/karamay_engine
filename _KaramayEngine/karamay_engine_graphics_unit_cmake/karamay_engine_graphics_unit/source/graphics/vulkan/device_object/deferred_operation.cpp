#include "deferred_operation.h"

deferred_operation::deferred_operation(device& dev) : device_object(dev)
{
	VkResult _result = device_khr_func(vkCreateDeferredOperationKHR)(_dev.handle(), nullptr, &_handle);
}

deferred_operation::~deferred_operation()
{
	device_khr_func(vkDestroyDeferredOperationKHR)(_dev.handle(), _handle, nullptr);
}

bool deferred_operation::join() noexcept
{
	if (!_handle) return false;

	device_khr_func(vkDeferredOperationJoinKHR)(_dev.handle(), _handle);
	return true;
}

std::optional<uint32> deferred_operation::max_concurrency() const noexcept
{
	if (!_handle) return std::nullopt;
	return device_khr_func(vkGetDeferredOperationMaxConcurrencyKHR)(_dev.handle(), _handle);
}

bool deferred_operation::get_result() const noexcept
{
	auto _result = device_khr_func(vkGetDeferredOperationResultKHR)(_dev.handle(), _handle);
	if (_result != VkResult::VK_SUCCESS)
	{
		return false;
	}
	return true;
}

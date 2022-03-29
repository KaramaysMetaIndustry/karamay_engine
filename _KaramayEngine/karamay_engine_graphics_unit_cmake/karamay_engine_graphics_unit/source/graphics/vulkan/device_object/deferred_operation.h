#ifndef DEFERRED_OPERATION_H
#define DEFERRED_OPERATION_H
#include "device_object.h"

class deferred_operation final : public device_object<VkDeferredOperationKHR>
{
public:

	deferred_operation(device& dev);

	deferred_operation(const deferred_operation&) = delete;
	deferred_operation& operator=(const deferred_operation&) = delete;

	~deferred_operation() override;

public:

	bool join() noexcept;

	bool get_result() const noexcept;

	std::optional<uint32> max_concurrency() const noexcept;
	
};



#endif
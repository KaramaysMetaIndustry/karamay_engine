#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FSemaphore final : public FDeviceObject<VkSemaphore>
{
	friend class FDevice;

	bool Allocate(VkSemaphoreType InType, uint64 InInitalValue);

public:

	FSemaphore(FDevice& InDevice);

	virtual ~FSemaphore() override;

	VkResult Wait(uint64 InValue, uint64 InTimeout);

	VkResult Signal(uint64 InValue);

	uint64 GetCounterValue();

};

_KANAS_CORE_END

#endif
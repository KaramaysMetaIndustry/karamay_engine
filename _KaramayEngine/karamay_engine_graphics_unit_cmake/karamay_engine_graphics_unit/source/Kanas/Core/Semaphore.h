#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class Semaphore final : public DeviceObject<VkSemaphore>
{
	friend class Device;

	bool Allocate(VkSemaphoreType InType, uint64 InInitalValue);

public:

	Semaphore(Device& InDevice);

	virtual ~Semaphore() override;

	VkResult Wait(uint64 InValue, uint64 InTimeout);

	VkResult Signal(uint64 InValue);

	uint64 GetCounterValue();

};

_KANAS_CORE_END

#endif
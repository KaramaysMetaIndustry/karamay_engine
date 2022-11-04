#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class Semaphore final : public DeviceObject<VkSemaphore>
{
public:

	Semaphore();

	virtual ~Semaphore();


};

_KANAS_CORE_END

#endif
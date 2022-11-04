#ifndef _FENCE_H_
#define _FENCE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class Fence final : public DeviceObject<VkFence>
{
public:

	VkFence();

	virtual ~VkFence();


};

_KANAS_CORE_END

#endif
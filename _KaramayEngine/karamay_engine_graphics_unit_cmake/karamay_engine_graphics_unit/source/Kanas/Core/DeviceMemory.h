#ifndef _DEVICE_MEMORY_H_
#define _DEVICE_MEMORY_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class DeviceMemory final : public DeviceObject<VkDeviceMemory>
{
public:

	DeviceMemory();

	virtual ~DeviceMemory();


};

_KANAS_CORE_END

#endif
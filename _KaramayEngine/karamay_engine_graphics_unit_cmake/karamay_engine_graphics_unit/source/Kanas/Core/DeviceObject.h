#ifndef _DEVICE_OBJECT_H_
#define _DEVICE_OBJECT_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class FDevice;
class FCommandBuffer;

template<typename VkHandleT>
class FDeviceObject : public VulkanObject<VkHandleT>
{

public:
	
	FDeviceObject(FDevice& InDevice) :
		Device(InDevice)
	{}

	virtual ~FDeviceObject()
	{
	}

private:

	FDevice& Device;

public:

	FDevice& GetDevice() { return Device; }

	const FDevice& GetDevice() const { return Device; }

};

_KANAS_CORE_END

#endif
#ifndef _DEVICE_OBJECT_H_
#define _DEVICE_OBJECT_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN


template<typename VkHandleT>
class DeviceObject : public VulkanObject<VkHandleT>
{

public:
	
	DeviceObject();

	virtual ~DeviceObject();

private:

	Device& _Device;

public:

	Device& GetDevice() { return _Device; }

	const Device& GetDevice() const { return _Device; }

};


_KANAS_CORE_END

#endif
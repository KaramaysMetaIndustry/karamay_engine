#ifndef _ACCELERATION_STRUCTURE_H_
#define _ACCELERATION_STRUCTURE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FDeviceMemory;

class FAccelerationStructure : FDeviceObject<VkAccelerationStructureKHR>
{
public:

	FAccelerationStructure(FDevice& InDevice);

	virtual ~FAccelerationStructure() override;
	

	TSharedPtr<FDeviceMemory> Mem;

};

_KANAS_CORE_END


#endif
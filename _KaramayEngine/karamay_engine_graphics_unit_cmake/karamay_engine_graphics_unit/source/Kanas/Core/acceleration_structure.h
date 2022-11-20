#ifndef _ACCELERATION_STRUCTURE_H_
#define _ACCELERATION_STRUCTURE_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class device_memory;

class acceleration_structue : device_object<VkAccelerationStructureKHR>
{
public:

	acceleration_structue(device& owner);

	virtual ~acceleration_structue() override;
	

	std::shared_ptr<device_memory> Mem;

};

_KANAS_CORE_END


#endif
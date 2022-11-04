#ifndef _DEVICE_H_
#define _DEVICE_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class PhysicalDevice;

class Device final : public VulkanObject<VkDevice>
{
public:
	Device() = default;

	virtual ~Device() {}

protected:

	bool Allocate();
	void Deallocate();

};

_KANAS_CORE_END


#endif

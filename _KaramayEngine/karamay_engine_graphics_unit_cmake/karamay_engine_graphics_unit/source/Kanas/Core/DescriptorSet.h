#ifndef _DESCRIPTOR_SET_H_
#define _DESCRIPTOR_SET_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class DescriptorPool;
class DescriptorSetLayout;

class DescriptorSet final : public DeviceObject<VkDescriptorSet>
{
public:

	DescriptorSet(Device& InDevice, DescriptorPool& InPool);

	virtual ~DescriptorSet();

	bool Allocate(DescriptorSetLayout& InLayout);

private:

	DescriptorPool& Pool;

};

_KANAS_CORE_END


#endif
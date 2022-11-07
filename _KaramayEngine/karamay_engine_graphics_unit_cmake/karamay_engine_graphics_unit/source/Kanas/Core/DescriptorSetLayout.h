#ifndef _DESCRIPTOR_SET_LAYOUT_H_
#define _DESCRIPTOR_SET_LAYOUT_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class DescriptorSetLayout final : public DeviceObject<VkDescriptorSetLayout>
{
public:

	DescriptorSetLayout(Device& InDevice);

	virtual ~DescriptorSetLayout();

	bool Allocate();

};

_KANAS_CORE_END

#endif
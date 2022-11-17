#ifndef _DESCRIPTOR_SET_LAYOUT_H_
#define _DESCRIPTOR_SET_LAYOUT_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FSampler;

class FDescriptorSetLayout final : public FDeviceObject<VkDescriptorSetLayout>
{
	bool Allocate();

public:

	FDescriptorSetLayout(FDevice& InDevice);

	virtual ~FDescriptorSetLayout();

	VkDescriptorSetLayoutBinding* GetBindingInfo(uint32 Binding) const;

private:

	TVector<VkDescriptorSetLayoutBinding> Bindings;

};

_KANAS_CORE_END

#endif
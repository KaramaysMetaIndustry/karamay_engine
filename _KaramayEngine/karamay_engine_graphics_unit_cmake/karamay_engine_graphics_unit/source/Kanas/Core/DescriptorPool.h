#ifndef _DESCRIPTOR_POOL_H_
#define _DESCRIPTOR_POOL_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN


class FDescriptorSet;
class FDescriptorSetLayout;

class FDescriptorPool final : public FDeviceObject<VkDescriptorPool>
{
	friend class FDevice;

	bool Allocate(const TVector<VkDescriptorPoolSize>& InPoolSizes, uint32 MaxSets);

public:

	FDescriptorPool(FDevice& InDevice);

	virtual ~FDescriptorPool();

	FDescriptorSet* CreateDescriptorSet(FDescriptorSetLayout& InSetLayout);

private:

	TVector<TUniquePtr<FDescriptorSet>> DescriptorSets;

};

_KANAS_CORE_END

#endif
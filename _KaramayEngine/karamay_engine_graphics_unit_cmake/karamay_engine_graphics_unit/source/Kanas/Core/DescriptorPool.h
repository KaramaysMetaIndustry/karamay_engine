#ifndef _DESCRIPTOR_POOL_H_
#define _DESCRIPTOR_POOL_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN


class DescriptorSet;
class DescriptorSetLayout;

class DescriptorPool final : public DeviceObject<VkDescriptorPool>
{
public:

	DescriptorPool(Device& InDevice);

	virtual ~DescriptorPool();

	bool Allocate();


	DescriptorSet* CreateDescriptorSet(DescriptorSetLayout& InSetLayout);


private:

	std::vector<std::unique_ptr<DescriptorSet>> DescriptorSets;

};

_KANAS_CORE_END

#endif
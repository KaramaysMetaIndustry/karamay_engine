#ifndef _PIPELINE_LAYOUT_H_
#define _PIPELINE_LAYOUT_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FDescriptorSetLayout;

class FPipelineLayout final : public FDeviceObject<VkPipelineLayout>
{
	friend class FDevice;

	bool Allocate(
		const TVector<TSharedPtr<FDescriptorSetLayout>>& InDescriptorSetLayouts, 
		const TVector<VkPushConstantRange>& InPushConstantRanges = {}
	);

public:

	FPipelineLayout(FDevice& InDevice);

	virtual ~FPipelineLayout() override;

	TSharedPtr<FDescriptorSetLayout> GetDescriptorSetLayout(uint32 SetIndex) const;

private:

	TVector<TSharedPtr<FDescriptorSetLayout>> DescriptorSetLayouts;

};


_KANAS_CORE_END

#endif
#ifndef _PIPELINE_LAYOUT_H_
#define _PIPELINE_LAYOUT_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class DescriptorSetLayout;

class PipelineLayout final : public DeviceObject<VkPipelineLayout>
{
public:

	PipelineLayout(Device& InDevice);

	virtual ~PipelineLayout() override;

public:

	bool Allocate(const std::vector<DescriptorSetLayout>& InDescriptorSetLayouts, const std::vector<VkPushConstantRange> InPushConstantRanges);

};


_KANAS_CORE_END

#endif
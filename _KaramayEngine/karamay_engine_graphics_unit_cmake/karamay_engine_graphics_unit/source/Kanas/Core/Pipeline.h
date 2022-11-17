#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FBuffer;
class FShaderModule;
class FPipelineLayout;
class FPipelineCache;
class FDescriptorSet;
class FCommandBuffer;

class FPipelineConstants
{

public:

	uint8* GetData();

	uint64 GetSize();
};


class FPipeline : public FDeviceObject<VkPipeline>
{
public:

	FPipeline(FDevice& InDevice, VkPipelineBindPoint InBindPoint);

	FPipeline(const FDevice&) = delete;
	FPipeline(FDevice&& Other);

	FPipeline& operator=(const FDevice&) = delete;

	virtual ~FPipeline() override;

	void CmdBind(FCommandBuffer& InRecorder);

	void CmdBindDescriptorSets(FCommandBuffer& InRecorder);

	void CmdPushConstants(FCommandBuffer& InRecorder);

	TSharedPtr<FPipelineLayout> GetLayout() const;

private:

	TSharedPtr<FPipelineLayout> Layout;

	VkPipelineBindPoint BindPoint;

	TSharedPtr<FPipelineConstants> Constants;

};

_KANAS_CORE_END

#endif
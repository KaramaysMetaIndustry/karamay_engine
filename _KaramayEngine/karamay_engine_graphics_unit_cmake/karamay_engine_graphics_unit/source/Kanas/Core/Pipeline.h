#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FCommandBuffer;
class FBuffer;
class FShaderModule;
class FPipelineLayout;
class FPipelineCache;

class FPipeline : public FDeviceObject<VkPipeline>
{
	friend class FDevice;

protected:

	bool Allocate();

public:

	FPipeline(FDevice& InDevice);

	virtual ~FPipeline();

	virtual void CmdBind(FCommandBuffer& InRecorder);

	void CmdPushConstants(FCommandBuffer& InRecorder, TVector<uint8>& InValues);

	TSharedPtr<FPipelineLayout> GetLayout();

	VkPipelineBindPoint GetBindPoint() const;

};

_KANAS_CORE_END

#endif
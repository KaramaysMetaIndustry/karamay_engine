#ifndef _COMPUTE_PIPELINE_H_
#define _COMPUTE_PIPELINE_H_

#include "Pipeline.h"

_KANAS_CORE_BEGIN

class FComputeShader;

class FComputePipeline final : public FPipeline
{

	friend class FDevice;

	bool Allocate(TSharedPtr<FComputeShader> ComputeShader, TSharedPtr<FPipelineLayout> Layout, TSharedPtr<FPipelineCache> Cache);

public:

	using BaseGroup = TArray<uint32, 3>;

	using GroupCount = TArray<uint32, 3>;

	FComputePipeline(FDevice& InDevice);

	virtual ~FComputePipeline();

	void CmdDispatch(FCommandBuffer& InRecorder, const GroupCount& InGroupCount);

	void CmdDispatchBase(FCommandBuffer& InRecorder, const BaseGroup& InBaseGroup, const GroupCount& InGroupCount);

	void CmdDispatchIndirect(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint64 InOffset);
};

_KANAS_CORE_END

#endif
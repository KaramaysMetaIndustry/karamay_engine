#ifndef _COMPUTE_PIPELINE_H_
#define _COMPUTE_PIPELINE_H_

#include "Pipeline.h"

_KANAS_CORE_BEGIN

class ComputePipeline final : public Pipeline
{
public:

	using BaseGroup = std::array<uint32, 3>;

	using GroupCount = std::array<uint32, 3>;

	ComputePipeline(Device& InDevice);

	virtual ~ComputePipeline();

	bool Allocate(PipelineCache& InCache, PipelineLayout& InLayout, ShaderModule& InComputeShaderModule);

	virtual void CmdBind(CommandBuffer& InRecorder) override;

	void CmdDispatch(CommandBuffer& InRecorder, const GroupCount& InGroupCount);

	void CmdDispatchBase(CommandBuffer& InRecorder, const BaseGroup& InBaseGroup, const GroupCount& InGroupCount);

	void CmdDispatchIndirect(CommandBuffer& InRecorder, Buffer& InBuffer, uint64 InOffset);
};

_KANAS_CORE_END

#endif
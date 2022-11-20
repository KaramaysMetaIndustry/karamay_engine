#ifndef _COMPUTE_PIPELINE_H_
#define _COMPUTE_PIPELINE_H_

#include "Pipeline.h"

_KANAS_CORE_BEGIN

class compute_shader;

class compute_pipeline final : public pipeline
{

	friend class device;

	bool alllocate(std::shared_ptr<compute_shader> ComputeShader, std::shared_ptr<pipeline_layout> Layout, std::shared_ptr<pipeline_cache> Cache);

public:

	using BaseGroup = TArray<std::uint32_t, 3>;

	using GroupCount = TArray<std::uint32_t, 3>;

	compute_pipeline(device& owner);

	virtual ~compute_pipeline();

	void CmdDispatch(command_buffer& InRecorder, const GroupCount& InGroupCount);

	void CmdDispatchBase(command_buffer& InRecorder, const BaseGroup& InBaseGroup, const GroupCount& InGroupCount);

	void CmdDispatchIndirect(command_buffer& InRecorder, buffer& InBuffer, std::uint64_t InOffset);
};

_KANAS_CORE_END

#endif
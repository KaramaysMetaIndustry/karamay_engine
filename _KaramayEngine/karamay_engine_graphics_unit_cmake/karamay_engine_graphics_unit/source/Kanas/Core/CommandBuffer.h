#ifndef _COMMAND_BUFFER_H_
#define _COMMAND_BUFFER_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class CommandPool;
class RenderPass;

class CommandBuffer final : public DeviceObject<VkCommandBuffer>
{
public:

	CommandBuffer(Device& InDevice, CommandPool& InCommandPool);

	virtual ~CommandBuffer() override;

	CommandPool& GetPool();

	enum class State : uint8
	{
		ReadyForBegin,
		IsInsideBegin,
		IsInsideRenderPass,
		HasEnded,
		Submitted,
		NotAllocated,
		NeedReset,
	};

	bool Allocate(VkCommandBufferLevel InCommandBufferLevel);

	void Reset(VkCommandBufferResetFlags InResetFlags);

	void Push(RenderPass* InRenderPass, uint32 InSubpassIndex, bool InOcclusionQueryEnable, VkQueryControlFlags InQueryControlFlags, VkQueryPipelineStatisticFlags InQueryPipelineStatisticFlags);

	void Submit();

	void Barrier();

private:

	CommandPool& Pool;

};

_KANAS_CORE_END


#endif
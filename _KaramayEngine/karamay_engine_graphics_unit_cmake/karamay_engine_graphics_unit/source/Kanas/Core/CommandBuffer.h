#ifndef _COMMAND_BUFFER_H_
#define _COMMAND_BUFFER_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class CommandPool;
class RenderPass;


namespace CommandList
{
	void CmdCopyBuffer();

	void CmdCopyImage();
	
};

class CommandBuffer final : public DeviceObject<VkCommandBuffer>
{

	bool Allocate(VkCommandBufferLevel InCommandBufferLevel);

public:

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

	CommandBuffer(Device& InDevice, CommandPool& InCommandPool);

	virtual ~CommandBuffer() override;

	void CmdBarrier();

	void CmdExecute();

	void CmdPush(RenderPass* InRenderPass, uint32 InSubpassIndex, bool InOcclusionQueryEnable, VkQueryControlFlags InQueryControlFlags, VkQueryPipelineStatisticFlags InQueryPipelineStatisticFlags);

	VkResult Reset(VkCommandBufferResetFlags InResetFlags);

	CommandPool& GetPool();

private:

	CommandPool& Pool;

	State CurrentState{ State::NotAllocated };


public:

	struct TransferCmds
	{
		CommandBuffer& CmdBufer;
		// Transfer
		void CmdCopyBuffer();
		void CmdCopyImage();
		void CmdCopyImageToBuffer();
		void CmdCopyBufferToImage();

		void CmdCopyQueryPoolResults();

		void CmdBlitImage();
		void CmdResolveImage();

		void CmdClearColorImage();
		void CmdClearDepthStencilImage();
	} Transfer;
	
	//
	void CmdClearAttachments()
	{
	}
	

};

_KANAS_CORE_END


#endif
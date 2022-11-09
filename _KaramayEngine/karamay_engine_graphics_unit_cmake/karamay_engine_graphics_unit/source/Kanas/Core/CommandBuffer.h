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

enum class CommandBufferState : uint8
{
	Initial,
	Recording,
	Executable,
	Pending,
	Invalid
};

enum class CommandBuffeLevel
{
	Primary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
	Secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY
};

class CommandBuffer : public DeviceObject<VkCommandBuffer>
{

	friend class CommandPool;

	bool Allocate(CommandBuffeLevel InCommandBufferLevel);

	CommandBufferState State;

public:

	CommandBuffer(Device& InDevice, CommandPool& InCommandPool);

	virtual ~CommandBuffer() override;

	void CmdBarrier();

	void CmdExecute();

	void CmdPush(RenderPass* InRenderPass, uint32 InSubpassIndex, bool InOcclusionQueryEnable, VkQueryControlFlags InQueryControlFlags, VkQueryPipelineStatisticFlags InQueryPipelineStatisticFlags);

	VkResult Reset(VkCommandBufferResetFlags InResetFlags);

	CommandPool& GetPool();

	CommandBufferState GetState() const { return State; }

private:

	CommandPool& Pool;

public:
	
	void CmdClearAttachments()
	{
	}
	

};


_KANAS_CORE_END


#endif
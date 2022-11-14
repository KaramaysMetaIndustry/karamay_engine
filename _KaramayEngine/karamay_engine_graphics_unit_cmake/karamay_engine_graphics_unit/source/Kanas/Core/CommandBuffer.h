#ifndef _COMMAND_BUFFER_H_
#define _COMMAND_BUFFER_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FCommandPool;
class FRenderPass;

enum class ECommandBufferState : uint8
{
	Initial,
	Recording,
	Executable,
	Pending,
	Invalid
};

enum class ECommandBuffeLevel
{
	Primary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
	Secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY
};

class FCommandBuffer : public FDeviceObject<VkCommandBuffer>
{

	friend class FCommandPool;

	bool Allocate(ECommandBuffeLevel InCommandBufferLevel);

	ECommandBufferState State;

public:

	FCommandBuffer(FDevice& InDevice, FCommandBuffer& InCommandPool);

	virtual ~FCommandBuffer() override;

	void CmdBarrier();

	void CmdExecute();

	void CmdPush(FRenderPass* InRenderPass, uint32 InSubpassIndex, bool InOcclusionQueryEnable, VkQueryControlFlags InQueryControlFlags, VkQueryPipelineStatisticFlags InQueryPipelineStatisticFlags);

	VkResult Reset(VkCommandBufferResetFlags InResetFlags);

	FCommandPool& GetPool();

	ECommandBufferState GetState() const { return State; }

private:

	FCommandPool& Pool;

public:
	
	void CmdClearAttachments()
	{
	}
	

};


_KANAS_CORE_END


#endif
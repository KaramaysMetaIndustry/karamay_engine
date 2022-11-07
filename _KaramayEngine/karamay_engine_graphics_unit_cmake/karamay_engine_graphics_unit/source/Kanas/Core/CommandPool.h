#ifndef _COMMAND_POOL_H_
#define _COMMAND_POOL_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class CommandBuffer;

class CommandPool final : public DeviceObject<VkCommandPool>
{
public:

	CommandPool(Device& InDevice);

	virtual ~CommandPool() override;

	bool Allocate(uint32 InQueueFamilyIndex);

	VkResult Reset(VkCommandPoolResetFlags InCommandPoolResetFlags);

	CommandBuffer* CreateCmdBuffer(VkCommandBufferLevel InCmdBufferLevel);

	void ReleaseCmdBuffer(CommandBuffer* InCmdBufferToRelease);

private:

	std::vector<std::unique_ptr<CommandBuffer>> CommandBuffers;

};

_KANAS_CORE_END

#endif
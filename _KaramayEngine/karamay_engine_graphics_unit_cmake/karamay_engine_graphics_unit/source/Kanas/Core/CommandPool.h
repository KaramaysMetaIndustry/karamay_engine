#ifndef _COMMAND_POOL_H_
#define _COMMAND_POOL_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class CommandBuffer;

class CommandPool final : public DeviceObject<VkCommandPool>
{

	bool bCanBufferResetSelf{ false };

	bool bTransientBuffer{ false };

public:

	CommandPool(Device& InDevice);

	virtual ~CommandPool() override;

	bool Allocate(uint32 InQueueFamilyIndex, bool bInTransientBuffer = false , bool bInCanBufferResetSelf = true);

	VkResult Reset(bool bInRecycle = false);

	CommandBuffer* CreateCmdBuffer(VkCommandBufferLevel InCmdBufferLevel);

	void ReleaseCmdBuffer(CommandBuffer* InCmdBufferToRelease);

	bool CanBufferReset() const;

	bool IsTransientBuffer() const;

private:

	std::vector<std::unique_ptr<CommandBuffer>> CommandBuffers;

};

_KANAS_CORE_END

#endif
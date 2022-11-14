#ifndef _COMMAND_POOL_H_
#define _COMMAND_POOL_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FCommandBuffer;

class FCommandPool final : public FDeviceObject<VkCommandPool>
{

	bool bCanBufferResetSelf{ false };

	bool bTransientBuffer{ false };

public:

	FCommandPool(FDevice& InDevice);

	virtual ~FCommandPool() override;

	bool Allocate(uint32 InQueueFamilyIndex, bool bInTransientBuffer = false , bool bInCanBufferResetSelf = true);

	VkResult Reset(bool bInRecycle = false);

	FCommandBuffer* CreateCmdBuffer(VkCommandBufferLevel InCmdBufferLevel);

	void ReleaseCmdBuffer(FCommandBuffer* InCmdBufferToRelease);

	bool CanBufferReset() const;

	bool IsTransientBuffer() const;

private:

	TVector<TUniquePtr<FCommandBuffer>> CmdBuffers;

};

_KANAS_CORE_END

#endif
#ifndef _EVENT_H_
#define _EVENT_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FCommandBuffer;

class FEvent final : public FDeviceObject<VkEvent>
{
	friend class FDevice;

	bool Allocate();

	VkResult GetStatus();

public:

	FEvent(FDevice& InDevice);

	virtual ~FEvent();

	void Set();

	void Reset();

	void CmdSet(FCommandBuffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags);

	void CmdReset(FCommandBuffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags);

	void CmdWait(FCommandBuffer& InRecorder);

};

_KANAS_CORE_END

#endif
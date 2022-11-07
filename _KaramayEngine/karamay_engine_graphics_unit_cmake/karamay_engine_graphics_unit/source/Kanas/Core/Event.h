#ifndef _EVENT_H_
#define _EVENT_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class CommandBuffer;

class Event final : public DeviceObject<VkEvent>
{
	friend class Event;

	bool Allocate();

	VkResult GetStatus();

public:

	Event(Device& InDevice);

	virtual ~Event();

	void Set();

	void Reset();

	void CmdSet(CommandBuffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags);

	void CmdReset(CommandBuffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags);

	void CmdWait(CommandBuffer& InRecorder);

};

_KANAS_CORE_END

#endif
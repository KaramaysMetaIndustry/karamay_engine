#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class CommandBuffer;
class Buffer;

class QueryPool : public DeviceObject<VkQueryPool>
{
public:

	QueryPool(Device& InDevice);

	virtual ~QueryPool() override;

	bool Allocate(VkQueryType InQueryType, uint32 InQueryCount);

	void CmdCopyResults(CommandBuffer& InRecorder, uint32 InFirstQuery, uint32 InQueryCount, Buffer& InDstBuffer, uint64 InDstOffset, uint64 InStride, VkQueryResultFlags InQueryResultFlags);

	void CmdReset(CommandBuffer& InRecorder, uint32 InFirstQuery, uint32 InQueryCount);

	void CmdBeginQuery(CommandBuffer& InRecorder, uint32 InQueryIndex, VkQueryControlFlags InQueryControlFlags);

	void CmdEndQuery(CommandBuffer& InRecorder, uint32 InQueryIndex);

};

_KANAS_CORE_END

#endif
#ifndef _PIPELINE_H_
#define _PIPELINE_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class CommandBuffer;
class Buffer;

class query_pool : public device_object<Vkquery_pool>
{
public:

	query_pool(Device& owner);

	virtual ~query_pool() override;

	bool alllocate(VkQueryType InQueryType, std::uint32_t InQueryCount);

	void CmdCopyResults(CommandBuffer& InRecorder, std::uint32_t InFirstQuery, std::uint32_t InQueryCount, Buffer& InDstBuffer, std::uint64_t InDstOffset, std::uint64_t InStride, VkQueryResultFlags InQueryResultFlags);

	void CmdReset(CommandBuffer& InRecorder, std::uint32_t InFirstQuery, std::uint32_t InQueryCount);

	void CmdBeginQuery(CommandBuffer& InRecorder, std::uint32_t InQueryIndex, VkQueryControlFlags InQueryControlFlags);

	void CmdEndQuery(CommandBuffer& InRecorder, std::uint32_t InQueryIndex);

};

_KANAS_CORE_END

#endif
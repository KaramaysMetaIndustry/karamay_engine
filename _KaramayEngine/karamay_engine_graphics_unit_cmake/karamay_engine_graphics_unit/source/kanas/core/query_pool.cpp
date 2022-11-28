#include "query_pool.h"
#include "device.h"
#include "command_buffer.h"
#include "buffer.h"

kanas::core::query_pool::query_pool(Device& owner) :
	device_object(owner)
{
}

kanas::core::query_pool::~query_pool()
{
	if (IsValid())
	{
		vkDestroyquery_pool(get_device().get_handle(), get_handle(), nullptr);

		reset_handle();
	}
}

bool kanas::core::query_pool::alllocate(VkQueryType InQueryType, std::uint32_t InQueryCount)
{
	Vkquery_poolCreateInfo query_poolCreateInfo;
	query_poolCreateInfo.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
	query_poolCreateInfo.pNext = nullptr;
	query_poolCreateInfo.flags;
	query_poolCreateInfo.queryType = InQueryType;
	query_poolCreateInfo.queryCount = InQueryCount;
	query_poolCreateInfo.pipelineStatistics;

	VkResult Result = vkCreatequery_pool(get_device().get_handle(), &query_poolCreateInfo, nullptr, &handle);
	
	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}
	
	return false;
}

void kanas::core::query_pool::CmdCopyResults(CommandBuffer& InRecorder, std::uint32_t InFirstQuery, std::uint32_t InQueryCount, Buffer& InDstBuffer, std::uint64_t InDstOffset, std::uint64_t InStride, VkQueryResultFlags InQueryResultFlags)
{
	vkCmdCopyquery_poolResults(InRecorder.get_handle(), get_handle(), InFirstQuery, InQueryCount, InDstBuffer.get_handle(), InDstOffset, InStride, InQueryResultFlags);
}

void kanas::core::query_pool::CmdReset(CommandBuffer& InRecorder, std::uint32_t InFirstQuery, std::uint32_t InQueryCount)
{
	vkCmdResetquery_pool(InRecorder.get_handle(), get_handle(), InFirstQuery, InQueryCount);
}

void kanas::core::query_pool::CmdBeginQuery(CommandBuffer& InRecorder, std::uint32_t InQueryIndex, VkQueryControlFlags InQueryControlFlags)
{
	vkCmdBeginQuery(InRecorder.get_handle(), get_handle(), InQueryIndex, InQueryControlFlags);
}

void kanas::core::query_pool::CmdEndQuery(CommandBuffer& InRecorder, std::uint32_t InQueryIndex)
{
	vkCmdEndQuery(InRecorder.get_handle(), get_handle(), InQueryIndex);
}

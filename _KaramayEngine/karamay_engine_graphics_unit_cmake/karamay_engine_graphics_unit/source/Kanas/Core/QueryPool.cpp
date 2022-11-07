#include "QueryPool.h"
#include "Device.h"
#include "CommandBuffer.h"
#include "Buffer.h"

Kanas::Core::QueryPool::QueryPool(Device& InDevice) :
	DeviceObject(InDevice)
{
}

Kanas::Core::QueryPool::~QueryPool()
{
	if (IsValid())
	{
		vkDestroyQueryPool(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

bool Kanas::Core::QueryPool::Allocate(VkQueryType InQueryType, uint32 InQueryCount)
{
	VkQueryPoolCreateInfo QueryPoolCreateInfo;
	QueryPoolCreateInfo.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
	QueryPoolCreateInfo.pNext = nullptr;
	QueryPoolCreateInfo.flags;
	QueryPoolCreateInfo.queryType = InQueryType;
	QueryPoolCreateInfo.queryCount = InQueryCount;
	QueryPoolCreateInfo.pipelineStatistics;

	VkResult Result = vkCreateQueryPool(GetDevice().GetHandle(), &QueryPoolCreateInfo, nullptr, &_Handle);
	
	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}
	
	return false;
}

void Kanas::Core::QueryPool::CmdCopyResults(CommandBuffer& InRecorder, uint32 InFirstQuery, uint32 InQueryCount, Buffer& InDstBuffer, uint64 InDstOffset, uint64 InStride, VkQueryResultFlags InQueryResultFlags)
{
	vkCmdCopyQueryPoolResults(InRecorder.GetHandle(), GetHandle(), InFirstQuery, InQueryCount, InDstBuffer.GetHandle(), InDstOffset, InStride, InQueryResultFlags);
}

void Kanas::Core::QueryPool::CmdReset(CommandBuffer& InRecorder, uint32 InFirstQuery, uint32 InQueryCount)
{
	vkCmdResetQueryPool(InRecorder.GetHandle(), GetHandle(), InFirstQuery, InQueryCount);
}

void Kanas::Core::QueryPool::CmdBeginQuery(CommandBuffer& InRecorder, uint32 InQueryIndex, VkQueryControlFlags InQueryControlFlags)
{
	vkCmdBeginQuery(InRecorder.GetHandle(), GetHandle(), InQueryIndex, InQueryControlFlags);
}

void Kanas::Core::QueryPool::CmdEndQuery(CommandBuffer& InRecorder, uint32 InQueryIndex)
{
	vkCmdEndQuery(InRecorder.GetHandle(), GetHandle(), InQueryIndex);
}

#include "Event.h"
#include "Device.h"
#include "CommandBuffer.h"

bool Kanas::Core::FEvent::Allocate()
{
	VkEventCreateInfo EventCreateInfo{};
	EventCreateInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
	EventCreateInfo.pNext = nullptr;
	EventCreateInfo.flags = {};

	const VkResult Result = vkCreateEvent(GetDevice().GetHandle(), &EventCreateInfo, nullptr, &_Handle);

	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

VkResult Kanas::Core::FEvent::GetStatus()
{
	return vkGetEventStatus(GetDevice().GetHandle(), GetHandle());
}

Kanas::Core::FEvent::FEvent(FDevice& InDevice) :
	FDeviceObject(InDevice)
{
}

Kanas::Core::FEvent::~FEvent()
{
	if (IsValid())
	{
		vkDestroyEvent(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

void Kanas::Core::FEvent::Set()
{
	VkResult Result = vkSetEvent(GetDevice().GetHandle(), GetHandle());
}

void Kanas::Core::FEvent::Reset()
{
	VkResult Result = vkResetEvent(GetDevice().GetHandle(), GetHandle());
}

void Kanas::Core::FEvent::CmdSet(FCommandBuffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags)
{
	vkCmdSetEvent(InRecorder.GetHandle(), GetHandle(), InPipelineStageFlags);
}

void Kanas::Core::FEvent::CmdReset(FCommandBuffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags)
{
	vkCmdResetEvent(InRecorder.GetHandle(), GetHandle(), InPipelineStageFlags);
}

void Kanas::Core::FEvent::CmdWait(FCommandBuffer& InRecorder)
{
	VkEvent EventHandles[] = { GetHandle() };
	VkPipelineStageFlags SrcMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
	VkPipelineStageFlags DstMask;

	std::vector<VkMemoryBarrier> MemBarriers;
	std::vector<VkBufferMemoryBarrier> BufferMemBarriers;
	std::vector<VkImageMemoryBarrier> ImageMemBarriers;

	vkCmdWaitEvents(InRecorder.GetHandle(), 1, EventHandles, SrcMask, DstMask, 
		static_cast<uint32>(MemBarriers.size()), MemBarriers.data(), 
		static_cast<uint32>(BufferMemBarriers.size()), BufferMemBarriers.data(), 
		static_cast<uint32>(ImageMemBarriers.size()), ImageMemBarriers.data()
	);
}

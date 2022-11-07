#include "Event.h"
#include "Device.h"
#include "CommandBuffer.h"

bool Kanas::Core::Event::Allocate()
{
	VkEventCreateInfo EventCreateInfo;
	EventCreateInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
	EventCreateInfo.pNext = nullptr;
	EventCreateInfo.flags = {};

	VkResult Result = vkCreateEvent(GetDevice().GetHandle(), &EventCreateInfo, nullptr, &_Handle);

	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

VkResult Kanas::Core::Event::GetStatus()
{
	return vkGetEventStatus(GetDevice().GetHandle(), GetHandle());
}

Kanas::Core::Event::Event(Device& InDevice) :
	DeviceObject(InDevice)
{
}

Kanas::Core::Event::~Event()
{
	if (IsValid())
	{
		vkDestroyEvent(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

void Kanas::Core::Event::Set()
{
	VkResult Result = vkSetEvent(GetDevice().GetHandle(), GetHandle());
}

void Kanas::Core::Event::Reset()
{
	VkResult Result = vkResetEvent(GetDevice().GetHandle(), GetHandle());
}

void Kanas::Core::Event::CmdSet(CommandBuffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags)
{
	vkCmdSetEvent(InRecorder.GetHandle(), GetHandle(), InPipelineStageFlags);
}

void Kanas::Core::Event::CmdReset(CommandBuffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags)
{
	vkCmdResetEvent(InRecorder.GetHandle(), GetHandle(), InPipelineStageFlags);
}

void Kanas::Core::Event::CmdWait(CommandBuffer& InRecorder)
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

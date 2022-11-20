#include "Event.h"
#include "Device.h"
#include "CommandBuffer.h"

bool kanas::core::FEvent::alllocate()
{
	VkEventCreateInfo EventCreateInfo{};
	EventCreateInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
	EventCreateInfo.pNext = nullptr;
	EventCreateInfo.flags = {};

	const VkResult Result = vkCreateEvent(get_device().get_handle(), &EventCreateInfo, nullptr, &handle);

	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

VkResult kanas::core::FEvent::GetStatus()
{
	return vkGetEventStatus(get_device().get_handle(), get_handle());
}

kanas::core::FEvent::FEvent(device& owner) :
	device_object(owner)
{
}

kanas::core::FEvent::~FEvent()
{
	if (IsValid())
	{
		vkDestroyEvent(get_device().get_handle(), get_handle(), nullptr);

		reset_handle();
	}
}

void kanas::core::FEvent::Set()
{
	VkResult Result = vkSetEvent(get_device().get_handle(), get_handle());
}

void kanas::core::FEvent::Reset()
{
	VkResult Result = vkResetEvent(get_device().get_handle(), get_handle());
}

void kanas::core::FEvent::CmdSet(command_buffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags)
{
	vkCmdSetEvent(InRecorder.get_handle(), get_handle(), InPipelineStageFlags);
}

void kanas::core::FEvent::CmdReset(command_buffer& InRecorder, VkPipelineStageFlags InPipelineStageFlags)
{
	vkCmdResetEvent(InRecorder.get_handle(), get_handle(), InPipelineStageFlags);
}

void kanas::core::FEvent::CmdWait(command_buffer& InRecorder)
{
	VkEvent EventHandles[] = { get_handle() };
	VkPipelineStageFlags SrcMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_ALL_COMMANDS_BIT;
	VkPipelineStageFlags DstMask;

	std::vector<VkMemoryBarrier> MemBarriers;
	std::vector<VkBufferMemoryBarrier> BufferMemBarriers;
	std::vector<VkImageMemoryBarrier> ImageMemBarriers;

	vkCmdWaitEvents(InRecorder.get_handle(), 1, EventHandles, SrcMask, DstMask, 
		static_cast<std::uint32_t>(MemBarriers.size()), MemBarriers.data(), 
		static_cast<std::uint32_t>(BufferMemBarriers.size()), BufferMemBarriers.data(), 
		static_cast<std::uint32_t>(ImageMemBarriers.size()), ImageMemBarriers.data()
	);
}

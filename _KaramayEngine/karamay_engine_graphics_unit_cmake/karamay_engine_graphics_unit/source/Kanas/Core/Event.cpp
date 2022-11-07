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
	vkCmdWaitEvents(InRecorder.GetHandle(), );
}

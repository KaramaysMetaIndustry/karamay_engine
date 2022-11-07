#include "Buffer.h"
#include "Device.h"
#include "CommandBuffer.h"
#include "Semaphore.h"

_KANAS_CORE_DECL::Buffer::Buffer(Device& InDevice) :
	DeviceObject(InDevice)
{
}

_KANAS_CORE_DECL::Buffer::~Buffer()
{
	if (IsValid())
	{
		vkDestroyBuffer(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

void _KANAS_CORE_DECL::Buffer::CmdCopy(CommandBuffer& InRecorder, Buffer& InDstBuffer, const std::vector<VkBufferCopy>& InRegions)
{
}

void _KANAS_CORE_DECL::Buffer::CmdCopy(CommandBuffer& InRecorder, Image& InDstImage, const std::vector<VkBufferImageCopy>& InRegions)
{
}

void _KANAS_CORE_DECL::Buffer::CmdFill(CommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, uint32 InData)
{
}

void _KANAS_CORE_DECL::Buffer::CmdUpdate(CommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, void* InData)
{
}

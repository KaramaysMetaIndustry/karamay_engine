#include "Buffer.h"
#include "Device.h"
#include "CommandBuffer.h"
#include "Semaphore.h"

bool Kanas::Core::Buffer::Allocate(VkDeviceSize InSize, VkBufferUsageFlags InUsageFlags, VkSharingMode InSharingMode)
{
	VkBufferCreateInfo BufferCreateInfo;
	BufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	BufferCreateInfo.pNext = nullptr;
	BufferCreateInfo.flags = {} ;
	BufferCreateInfo.size = InSize;
	BufferCreateInfo.usage = InUsageFlags;
	BufferCreateInfo.sharingMode = InSharingMode;
	BufferCreateInfo.queueFamilyIndexCount = 0;
	BufferCreateInfo.pQueueFamilyIndices = nullptr;

	const VkResult Result = vkCreateBuffer(GetDevice().GetHandle(), &BufferCreateInfo, nullptr, &_Handle);
	
	if (Result == VkResult::VK_SUCCESS)
	{
		VkMemoryRequirements MemRequirements;
		vkGetBufferMemoryRequirements(GetDevice().GetHandle(), GetHandle(), &MemRequirements);

		const uint64 MemAllocSize = MemRequirements.size;
		const uint32 MemTypeIndex = 0;

		Mem = GetDevice().CreateDeviceMemory(MemAllocSize, MemTypeIndex);

		if (Mem)
		{
			return true;
		}
	}

	return false;
}

Kanas::Core::Buffer::Buffer(Device& InDevice) :
	DeviceObject(InDevice)
{
}

Kanas::Core::Buffer::~Buffer()
{
	if (IsValid())
	{
		vkDestroyBuffer(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

void Kanas::Core::Buffer::CmdCopy(CommandBuffer& InRecorder, Buffer& InDstBuffer, const std::vector<VkBufferCopy>& InRegions)
{
}

void Kanas::Core::Buffer::CmdCopy(CommandBuffer& InRecorder, Image& InDstImage, const std::vector<VkBufferImageCopy>& InRegions)
{
}

void Kanas::Core::Buffer::CmdFill(CommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, uint32 InData)
{
}

void Kanas::Core::Buffer::CmdUpdate(CommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, void* InData)
{
}

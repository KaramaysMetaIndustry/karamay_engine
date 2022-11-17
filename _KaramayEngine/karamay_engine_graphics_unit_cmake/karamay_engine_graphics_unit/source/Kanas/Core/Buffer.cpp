#include "Buffer.h"
#include "Device.h"
#include "PhysicalDevice.h"
#include "CommandBuffer.h"
#include "Semaphore.h"
#include "Image.h"
#include "DeviceMemory.h"

bool Kanas::Core::FBuffer::Allocate(uint64 Size, FBufferUsageFlags UsageFlags, TSharedPtr<FConcurrentGuide> InConcurrentGuide)
{
	if (Size == 0)
	{
		return false;
	}

	VkBufferCreateInfo BufferCreateInfo{};
	BufferCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	BufferCreateInfo.pNext = nullptr;
	BufferCreateInfo.flags = {} ;
	BufferCreateInfo.size = Size;
	BufferCreateInfo.usage = UsageFlags.Get();
	
	if (InConcurrentGuide && InConcurrentGuide->DoesSupportConcurrency())
	{
		TVector<uint32> QueueFamilyIndices;
		InConcurrentGuide->GetConcurrentFamilyIndices(QueueFamilyIndices);
		// family index count must > 1
		BufferCreateInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
		BufferCreateInfo.queueFamilyIndexCount = static_cast<uint32>(QueueFamilyIndices.size());
		BufferCreateInfo.pQueueFamilyIndices = QueueFamilyIndices.data();
	}
	else {
		BufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		BufferCreateInfo.queueFamilyIndexCount = 0;
		BufferCreateInfo.pQueueFamilyIndices = nullptr;
	}

	const VkResult BufferCreationResult = vkCreateBuffer(GetDevice().GetHandle(), &BufferCreateInfo, nullptr, &_Handle);
	
	if (BufferCreationResult == VkResult::VK_SUCCESS)
	{
		VkMemoryRequirements MemRequirements;
		vkGetBufferMemoryRequirements(GetDevice().GetHandle(), GetHandle(), &MemRequirements);

		const uint64 MemAllocSize = MemRequirements.size;
		const uint32 MemTypeIndex = 0;

		TUniquePtr<FDeviceMemory> NewMem = MakeUnique<FDeviceMemory>(GetDevice());

		if (NewMem && NewMem->Allocate(MemAllocSize, MemTypeIndex))
		{
			const VkResult BufferBindingResult = vkBindBufferMemory(GetDevice().GetHandle(), GetHandle(), Mem->GetHandle(), 0);

			if (BufferBindingResult == VkResult::VK_SUCCESS)
			{
				Mem = MoveTemp(NewMem);
				return true;
			}
		}
	}

	return false;
}

Kanas::Core::FBuffer::FBuffer(FDevice& InDevice) :
	FDeviceObject(InDevice)
{
	
}

Kanas::Core::FBuffer::FBuffer(FBuffer&& Other) noexcept :
	FDeviceObject(Other.GetDevice())
{
	_Handle = Other.GetHandle();
	Other.ResetHandle();
}

Kanas::Core::FBuffer::~FBuffer()
{
	if (IsValid())
	{
		vkDestroyBuffer(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

void Kanas::Core::FBuffer::CmdCopy(FCommandBuffer& InRecorder, FBuffer& InDstBuffer, const TVector<VkBufferCopy>& InRegions)
{
	vkCmdCopyBuffer(InRecorder.GetHandle(), GetHandle(), InDstBuffer.GetHandle(), static_cast<uint32>(InRegions.size()), InRegions.data());
}

void Kanas::Core::FBuffer::CmdCopyToImage(FCommandBuffer& InRecorder, FImage& InDstImage, const TVector<VkBufferImageCopy>& InRegions)
{
	vkCmdCopyBufferToImage(InRecorder.GetHandle(), GetHandle(), InDstImage.GetHandle(), InDstImage.GetLayout(), static_cast<uint32>(InRegions.size()), InRegions.data());
}

void Kanas::Core::FBuffer::CmdFill(FCommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, uint32 InData)
{
	vkCmdFillBuffer(InRecorder.GetHandle(), GetHandle(), InOffset, InSize, InData);
}

void Kanas::Core::FBuffer::CmdUpdate(FCommandBuffer& InRecorder, uint64 InOffset, uint64 InSize, void* InData)
{
	vkCmdUpdateBuffer(InRecorder.GetHandle(), GetHandle(), InOffset, InSize, InData);
}

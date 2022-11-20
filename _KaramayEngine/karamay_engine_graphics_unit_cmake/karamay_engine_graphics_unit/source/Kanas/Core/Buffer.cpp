#include "buffer.h"
#include "device.h"
#include "physical_device.h"
#include "command_buffer.h"
#include "semaphore.h"
#include "image.h"
#include "device_memory.h"

bool kanas::core::buffer::alllocate(std::uint64_t Size, buffer_usage_flags UsageFlags, std::shared_ptr<FConcurrentGuide> InConcurrentGuide)
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
	BufferCreateInfo.usage = UsageFlags.get();
	
	if (InConcurrentGuide && InConcurrentGuide->DoesSupportConcurrency())
	{
		std::vector<std::uint32_t> QueueFamilyIndices;
		InConcurrentGuide->GetConcurrentFamilyIndices(QueueFamilyIndices);
		// family index count must > 1
		BufferCreateInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
		BufferCreateInfo.queueFamilyIndexCount = static_cast<std::uint32_t>(QueueFamilyIndices.size());
		BufferCreateInfo.pQueueFamilyIndices = QueueFamilyIndices.data();
	}
	else {
		BufferCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		BufferCreateInfo.queueFamilyIndexCount = 0;
		BufferCreateInfo.pQueueFamilyIndices = nullptr;
	}

	const VkResult BufferCreationResult = vkCreateBuffer(get_device().get_handle(), &BufferCreateInfo, nullptr, &handle);
	
	if (BufferCreationResult == VK_SUCCESS)
	{
		VkMemoryRequirements MemRequirements;
		vkGetBufferMemoryRequirements(get_device().get_handle(), get_handle(), &MemRequirements);

		const std::uint64_t MemAllocSize = MemRequirements.size;
		const std::uint32_t MemTypeIndex = 0;

		std::unique_ptr<device_memory> NewMem = std::make_unique<device_memory>(get_device());

		if (NewMem && NewMem->alllocate(MemAllocSize, MemTypeIndex))
		{
			const VkResult BufferBindingResult = vkBindBufferMemory(get_device().get_handle(), get_handle(), Mem->get_handle(), 0);

			if (BufferBindingResult == VkResult::VK_SUCCESS)
			{
				Mem = std::move(NewMem);
				return true;
			}
		}
	}

	return false;
}

kanas::core::buffer::buffer(device& owner) :
	device_object(owner)
{
	
}

kanas::core::buffer::buffer(buffer&& Other) noexcept :
	device_object(Other.get_device())
{
	handle = Other.get_handle();
	Other.reset_handle();
}

kanas::core::buffer::~buffer()
{
	if (IsValid())
	{
		vkDestroyBuffer(get_device().get_handle(), get_handle(), nullptr);

		reset_handle();
	}
}

void kanas::core::buffer::CmdCopy(command_buffer& InRecorder, buffer& InDstBuffer, const std::vector<VkBufferCopy>& InRegions)
{
	vkCmdCopyBuffer(InRecorder.get_handle(), get_handle(), InDstBuffer.get_handle(), static_cast<std::uint32_t>(InRegions.size()), InRegions.data());
}

void kanas::core::buffer::CmdCopyToImage(command_buffer& InRecorder, image& InDstImage, const std::vector<VkBufferImageCopy>& InRegions)
{
	vkCmdCopyBufferToImage(InRecorder.get_handle(), get_handle(), InDstImage.get_handle(), InDstImage.GetLayout(), static_cast<std::uint32_t>(InRegions.size()), InRegions.data());
}

void kanas::core::buffer::CmdFill(command_buffer& InRecorder, std::uint64_t InOffset, std::uint64_t InSize, std::uint32_t InData)
{
	vkCmdFillBuffer(InRecorder.get_handle(), get_handle(), InOffset, InSize, InData);
}

void kanas::core::buffer::CmdUpdate(command_buffer& InRecorder, std::uint64_t InOffset, std::uint64_t InSize, void* InData)
{
	vkCmdUpdateBuffer(InRecorder.get_handle(), get_handle(), InOffset, InSize, InData);
}

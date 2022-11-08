#include "Image.h"
#include "Device.h"
#include "PhysicalDevice.h"
#include "DeviceMemory.h"

bool Kanas::Core::Image::Allocate()
{
	VkImageCreateInfo ImageCreateInfo;
	ImageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	ImageCreateInfo.pNext = nullptr;
	ImageCreateInfo.flags = {};
	ImageCreateInfo.imageType;
	ImageCreateInfo.format;
	ImageCreateInfo.extent;
	ImageCreateInfo.mipLevels;
	ImageCreateInfo.arrayLayers;
	ImageCreateInfo.samples;
	ImageCreateInfo.tiling;
	ImageCreateInfo.usage;
	ImageCreateInfo.sharingMode;
	ImageCreateInfo.queueFamilyIndexCount;
	ImageCreateInfo.pQueueFamilyIndices;
	ImageCreateInfo.initialLayout;

	const VkResult Result = vkCreateImage(GetDevice().GetHandle(), &ImageCreateInfo, nullptr, &_Handle);

	if (Result == VkResult::VK_SUCCESS)
	{
		VkMemoryRequirements MemoryRequirements;
		vkGetImageMemoryRequirements(GetDevice().GetHandle(), GetHandle(), &MemoryRequirements);

		const uint64 MemAllocSize = MemoryRequirements.size;
		const uint32 MemTypeIndex = 0;

		Mem = GetDevice().CreateDeviceMemory(MemAllocSize, MemTypeIndex);

		if(Mem)
		{
			const VkDeviceSize MemOffset = 0;
			const VkResult BindImageResult = vkBindImageMemory(GetDevice().GetHandle(), GetHandle(), Mem->GetHandle(), MemOffset);
			
			if (BindImageResult == VkResult::VK_SUCCESS)
			{
				return true;
			}
		}
	}

	return false;
}

Kanas::Core::Image::Image(Device& InDevice) :
	DeviceObject(InDevice)
{
	std::vector<VkQueueFamilyProperties> QueueFamilyPropertiesArr;
	GetDevice().GetPhysicalDevice().GetQueueFamilyProperties(QueueFamilyPropertiesArr);

}

Kanas::Core::Image::~Image()
{
	if (IsValid())
	{
		vkDestroyImage(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

void Kanas::Core::Image::CmdClear(CommandBuffer& InRecorder, const VkClearColorValue& InValue, const std::vector<VkImageSubresourceRange>& InRanges)
{
}

void Kanas::Core::Image::CmdClear(CommandBuffer& InRecorder, const VkClearDepthStencilValue& InValue, const std::vector<VkImageSubresourceRange>& InRanges)
{
}

void Kanas::Core::Image::CmdCopy(CommandBuffer& InRecorder, Buffer& InDstBuffer, const std::vector<VkBufferImageCopy>& InRegions)
{
}

void Kanas::Core::Image::CmdCopy(CommandBuffer& InRecorder, Image& InDstImage, const std::vector<VkImageCopy>& InRegions)
{
}

void Kanas::Core::Image::CmdBlit(CommandBuffer& InRecorder, Image& InDstImage, const std::vector<VkImageBlit>& InRegions, VkFilter InFilter)
{
}

void Kanas::Core::Image::CmdResolve(CommandBuffer& InRecorder, Image& InDstImage, const std::vector<VkImageResolve>& InRegions)
{
}

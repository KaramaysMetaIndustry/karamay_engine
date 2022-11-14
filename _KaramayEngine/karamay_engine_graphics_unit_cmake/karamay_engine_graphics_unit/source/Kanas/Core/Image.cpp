#include "Image.h"
#include "Device.h"
#include "PhysicalDevice.h"
#include "DeviceMemory.h"
#include "CommandBuffer.h"
#include "Buffer.h"
#include "ImageView.h"

bool Kanas::Core::Image::Allocate(VkImageType InType, VkFormat InFormat, VkExtent3D InExtent, uint32 InMips, uint32 InLayers, VkSampleCountFlagBits InSamples, VkImageTiling InTileing, VkImageUsageFlags InUsage, VkSharingMode InSharingMode, VkImageLayout InInitalLayout)
{
	VkImageCreateInfo ImageCreateInfo;
	ImageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	ImageCreateInfo.pNext = nullptr;
	ImageCreateInfo.flags = {};
	ImageCreateInfo.imageType = InType; VkImageType::VK_IMAGE_TYPE_3D;
	ImageCreateInfo.format = InFormat; VkFormat::VK_FORMAT_A1R5G5B5_UNORM_PACK16;
	ImageCreateInfo.extent = InExtent; VkExtent3D;
	ImageCreateInfo.mipLevels = InMips;
	ImageCreateInfo.arrayLayers = InLayers;
	ImageCreateInfo.samples = InSamples; VkSampleCountFlagBits::VK_SAMPLE_COUNT_16_BIT;
	ImageCreateInfo.tiling = InTileing; VkImageTiling::VK_IMAGE_TILING_LINEAR;
	ImageCreateInfo.usage = InUsage; VkImageUsageFlagBits::VK_IMAGE_USAGE_STORAGE_BIT;
	ImageCreateInfo.sharingMode = InSharingMode;
	ImageCreateInfo.queueFamilyIndexCount;
	ImageCreateInfo.pQueueFamilyIndices;
	ImageCreateInfo.initialLayout = InInitalLayout;

	const VkResult Result = vkCreateImage(GetDevice().GetHandle(), &ImageCreateInfo, nullptr, &_Handle);

	if (Result == VkResult::VK_SUCCESS)
	{
		VkMemoryRequirements MemoryRequirements;
		vkGetImageMemoryRequirements(GetDevice().GetHandle(), GetHandle(), &MemoryRequirements);

		const uint64 MemAllocSize = MemoryRequirements.size;
		const uint32 MemTypeIndex = 0;

		TUniquePtr<DeviceMemory> NewMem = std::make_unique<DeviceMemory>(GetDevice());
		if (NewMem && NewMem->Allocate(MemAllocSize, MemTypeIndex))
		{
			const VkDeviceSize MemOffset = 0;
			const VkResult BindImageResult = vkBindImageMemory(GetDevice().GetHandle(), GetHandle(), Mem->GetHandle(), MemOffset);

			if (BindImageResult == VkResult::VK_SUCCESS)
			{

				Mem = std::move(NewMem);
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
	vkCmdClearColorImage(InRecorder.GetHandle(), GetHandle(), Layout, &InValue, static_cast<uint32>(InRanges.size()), InRanges.data());
}

void Kanas::Core::Image::CmdClear(CommandBuffer& InRecorder, const VkClearDepthStencilValue& InValue, const TVector<VkImageSubresourceRange>& InRanges)
{
	vkCmdClearDepthStencilImage(InRecorder.GetHandle(), GetHandle(), Layout, &InValue, static_cast<uint32>(InRanges.size()), InRanges.data());
}

void Kanas::Core::Image::CmdCopy(CommandBuffer& InRecorder, Buffer& InDstBuffer, const TVector<VkBufferImageCopy>& InRegions)
{
	vkCmdCopyImageToBuffer(InRecorder.GetHandle(), GetHandle(), Layout, InDstBuffer.GetHandle(), static_cast<uint32>(InRegions.size()), InRegions.data());
}

void Kanas::Core::Image::CmdCopy(CommandBuffer& InRecorder, Image& InDstImage, const TVector<VkImageCopy>& InRegions)
{
	vkCmdCopyImage(InRecorder.GetHandle(), GetHandle(), Layout, InDstImage.GetHandle(), InDstImage.GetLayout(), static_cast<uint32>(InRegions.size()), InRegions.data());;
}

void Kanas::Core::Image::CmdBlit(CommandBuffer& InRecorder, Image& InDstImage, const TVector<VkImageBlit>& InRegions, VkFilter InFilter)
{
	vkCmdBlitImage(InRecorder.GetHandle(), GetHandle(), Layout, InDstImage.GetHandle(), InDstImage.GetLayout(), static_cast<uint32>(InRegions.size()), InRegions.data(), InFilter);;
}

void Kanas::Core::Image::CmdResolve(CommandBuffer& InRecorder, Image& InDstImage, const TVector<VkImageResolve>& InRegions)
{
	vkCmdResolveImage(InRecorder.GetHandle(), GetHandle(), Layout, InDstImage.GetHandle(), InDstImage.GetLayout(), static_cast<uint32>(InRegions.size()), InRegions.data());;
}

VkImageLayout Kanas::Core::Image::GetLayout()
{
	return Layout;
}

Kanas::Core::TSharedPtr<Kanas::Core::ImageView> Kanas::Core::Image::CreateView(VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange)
{
	TSharedPtr<ImageView> NewImageView = std::make_shared<ImageView>(GetDevice());
	
	if (NewImageView && NewImageView->Allocate(shared_from_this(), InViewType, InFormat, InComponents, InSubresourceRange))
	{
		return NewImageView;
	}

	return nullptr;
}

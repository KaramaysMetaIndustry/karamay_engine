#include "Image.h"
#include "ImageView.h"
#include "PhysicalDevice.h"
#include "Device.h"
#include "DeviceMemory.h"
#include "Buffer.h"
#include "CommandBuffer.h"

bool Kanas::Core::FImage::Allocate(VkImageType InType, VkFormat InFormat, VkExtent3D InExtent, uint32 InMips, uint32 InLayers, VkSampleCountFlagBits InSamples, VkImageTiling InTileing, FImageUsageFlags Usage, VkImageLayout InInitalLayout, TSharedPtr<FConcurrentGuide> ConcurrentGuide)
{
	VkImageCreateInfo ImageCreateInfo{};
	ImageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	ImageCreateInfo.pNext = nullptr;
	ImageCreateInfo.flags = {};
	ImageCreateInfo.imageType = InType;
	ImageCreateInfo.format = InFormat;
	ImageCreateInfo.extent = InExtent;
	ImageCreateInfo.mipLevels = InMips;
	ImageCreateInfo.arrayLayers = InLayers;
	ImageCreateInfo.samples = InSamples;
	ImageCreateInfo.tiling = InTileing;
	ImageCreateInfo.usage = Usage.Get();
	
	if (ConcurrentGuide && ConcurrentGuide->DoesSupportConcurrency())
	{
		TVector<uint32> ConcurrentQueueFamilyIndices;
		ConcurrentGuide->GetConcurrentFamilyIndices(ConcurrentQueueFamilyIndices);
		ImageCreateInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
		ImageCreateInfo.queueFamilyIndexCount = static_cast<uint32>(ConcurrentQueueFamilyIndices.size());
		ImageCreateInfo.pQueueFamilyIndices = ConcurrentQueueFamilyIndices.data();
	}
	else {
		ImageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		ImageCreateInfo.queueFamilyIndexCount = 0;
		ImageCreateInfo.pQueueFamilyIndices = nullptr;
	}
	
	ImageCreateInfo.initialLayout = InInitalLayout;

	const VkResult ImageCreationResult = vkCreateImage(GetDevice().GetHandle(), &ImageCreateInfo, nullptr, &_Handle);

	if (ImageCreationResult == VK_SUCCESS)
	{
		VkMemoryRequirements MemoryRequirements;
		vkGetImageMemoryRequirements(GetDevice().GetHandle(), GetHandle(), &MemoryRequirements);

		const uint64 MemAllocSize = MemoryRequirements.size;
		const uint32 MemTypeIndex = 0;

		TUniquePtr<FDeviceMemory> NewMem = std::make_unique<FDeviceMemory>(GetDevice());
		if (NewMem && NewMem->Allocate(MemAllocSize, MemTypeIndex))
		{
			const VkDeviceSize MemOffset = 0;
			const VkResult ImageBindingResult = vkBindImageMemory(GetDevice().GetHandle(), GetHandle(), Mem->GetHandle(), MemOffset);

			if (ImageBindingResult == VK_SUCCESS)
			{
				Mem = MoveTemp(NewMem);
				return true;
			}
		}
	}

	return false;
}

Kanas::Core::FImage::FImage(FDevice& InDevice) :
	FDeviceObject(InDevice)
{
}

Kanas::Core::FImage::FImage(FImage&& Other) :
	FDeviceObject(Other.GetDevice())
{
}

Kanas::Core::FImage::~FImage()
{
	if (IsValid())
	{
		vkDestroyImage(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

void Kanas::Core::FImage::CmdClear(FCommandBuffer& InRecorder, const VkClearColorValue& InValue, const TVector<VkImageSubresourceRange>& InRanges)
{
	vkCmdClearColorImage(InRecorder.GetHandle(), GetHandle(), Layout, &InValue, static_cast<uint32>(InRanges.size()), InRanges.data());
}

void Kanas::Core::FImage::CmdClear(FCommandBuffer& InRecorder, const VkClearDepthStencilValue& InValue, const TVector<VkImageSubresourceRange>& InRanges)
{
	vkCmdClearDepthStencilImage(InRecorder.GetHandle(), GetHandle(), Layout, &InValue, static_cast<uint32>(InRanges.size()), InRanges.data());
}

void Kanas::Core::FImage::CmdCopy(FCommandBuffer& InRecorder, FBuffer& InDstBuffer, const TVector<VkBufferImageCopy>& InRegions)
{
	vkCmdCopyImageToBuffer(InRecorder.GetHandle(), GetHandle(), Layout, InDstBuffer.GetHandle(), static_cast<uint32>(InRegions.size()), InRegions.data());
}

void Kanas::Core::FImage::CmdCopy(FCommandBuffer& InRecorder, FImage& InDstImage, const TVector<VkImageCopy>& InRegions)
{
	vkCmdCopyImage(InRecorder.GetHandle(), GetHandle(), Layout, InDstImage.GetHandle(), InDstImage.GetLayout(), static_cast<uint32>(InRegions.size()), InRegions.data());;
}

void Kanas::Core::FImage::CmdBlit(FCommandBuffer& InRecorder, FImage& InDstImage, const TVector<VkImageBlit>& InRegions, VkFilter InFilter)
{
	vkCmdBlitImage(InRecorder.GetHandle(), GetHandle(), Layout, InDstImage.GetHandle(), InDstImage.GetLayout(), static_cast<uint32>(InRegions.size()), InRegions.data(), InFilter);;
}

void Kanas::Core::FImage::CmdResolve(FCommandBuffer& InRecorder, FImage& InDstImage, const TVector<VkImageResolve>& InRegions)
{
	vkCmdResolveImage(InRecorder.GetHandle(), GetHandle(), Layout, InDstImage.GetHandle(), InDstImage.GetLayout(), static_cast<uint32>(InRegions.size()), InRegions.data());
}

VkImageLayout Kanas::Core::FImage::GetLayout()
{
	return Layout;
}

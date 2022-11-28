#include "image.h"
#include "image_view.h"
#include "physical_device.h"
#include "device.h"
#include "device_memory.h"
#include "buffer.h"
#include "command_buffer.h"

bool kanas::core::image::alllocate(VkImageType InType, VkFormat InFormat, VkExtent3D InExtent, std::uint32_t InMips, std::uint32_t InLayers, VkSampleCountFlagBits InSamples, VkImageTiling InTileing, image_usage_flags Usage, VkImageLayout InInitalLayout, std::shared_ptr<FConcurrentGuide> ConcurrentGuide)
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
		std::vector<std::uint32_t> ConcurrentQueueFamilyIndices;
		ConcurrentGuide->GetConcurrentFamilyIndices(ConcurrentQueueFamilyIndices);
		ImageCreateInfo.sharingMode = VK_SHARING_MODE_CONCURRENT;
		ImageCreateInfo.queueFamilyIndexCount = static_cast<std::uint32_t>(ConcurrentQueueFamilyIndices.size());
		ImageCreateInfo.pQueueFamilyIndices = ConcurrentQueueFamilyIndices.data();
	}
	else {
		ImageCreateInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
		ImageCreateInfo.queueFamilyIndexCount = 0;
		ImageCreateInfo.pQueueFamilyIndices = nullptr;
	}
	
	ImageCreateInfo.initialLayout = InInitalLayout;

	const VkResult ImageCreationResult = vkCreateImage(get_device().get_handle(), &ImageCreateInfo, nullptr, &handle);

	if (ImageCreationResult == VK_SUCCESS)
	{
		VkMemoryRequirements MemoryRequirements;
		vkGetImageMemoryRequirements(get_device().get_handle(), get_handle(), &MemoryRequirements);

		const std::uint64_t MemAllocSize = MemoryRequirements.size;
		const std::uint32_t MemTypeIndex = 0;

		std::unique_ptr<device_memory> NewMem = std::make_unique<device_memory>(get_device());
		if (NewMem && NewMem->alllocate(MemAllocSize, MemTypeIndex))
		{
			const VkDeviceSize MemOffset = 0;
			const VkResult ImageBindingResult = vkBindImageMemory(get_device().get_handle(), get_handle(), Mem->get_handle(), MemOffset);

			if (ImageBindingResult == VK_SUCCESS)
			{
				Mem = std::move(NewMem);
				return true;
			}
		}
	}

	return false;
}

kanas::core::image::image(device& owner) :
	device_object(owner)
{
}

kanas::core::image::image(image&& Other) :
	device_object(Other.get_device())
{
}

kanas::core::image::~image()
{
	if (IsValid())
	{
		vkDestroyImage(get_device().get_handle(), get_handle(), nullptr);

		reset_handle();
	}
}

void kanas::core::image::CmdClear(command_buffer& InRecorder, const VkClearColorValue& InValue, const std::vector<VkImageSubresourceRange>& InRanges)
{
	vkCmdClearColorImage(InRecorder.get_handle(), get_handle(), Layout, &InValue, static_cast<std::uint32_t>(InRanges.size()), InRanges.data());
}

void kanas::core::image::CmdClear(command_buffer& InRecorder, const VkClearDepthStencilValue& InValue, const std::vector<VkImageSubresourceRange>& InRanges)
{
	vkCmdClearDepthStencilImage(InRecorder.get_handle(), get_handle(), Layout, &InValue, static_cast<std::uint32_t>(InRanges.size()), InRanges.data());
}

void kanas::core::image::CmdCopy(command_buffer& InRecorder, buffer& InDstBuffer, const std::vector<VkBufferImageCopy>& InRegions)
{
	vkCmdCopyImageToBuffer(InRecorder.get_handle(), get_handle(), Layout, InDstBuffer.get_handle(), static_cast<std::uint32_t>(InRegions.size()), InRegions.data());
}

void kanas::core::image::CmdCopy(command_buffer& InRecorder, image& InDstImage, const std::vector<VkImageCopy>& InRegions)
{
	vkCmdCopyImage(InRecorder.get_handle(), get_handle(), Layout, InDstImage.get_handle(), InDstImage.GetLayout(), static_cast<std::uint32_t>(InRegions.size()), InRegions.data());;
}

void kanas::core::image::CmdBlit(command_buffer& InRecorder, image& InDstImage, const std::vector<VkImageBlit>& InRegions, VkFilter InFilter)
{
	vkCmdBlitImage(InRecorder.get_handle(), get_handle(), Layout, InDstImage.get_handle(), InDstImage.GetLayout(), static_cast<std::uint32_t>(InRegions.size()), InRegions.data(), InFilter);;
}

void kanas::core::image::CmdResolve(command_buffer& InRecorder, image& InDstImage, const std::vector<VkImageResolve>& InRegions)
{
	vkCmdResolveImage(InRecorder.get_handle(), get_handle(), Layout, InDstImage.get_handle(), InDstImage.GetLayout(), static_cast<std::uint32_t>(InRegions.size()), InRegions.data());
}

VkImageLayout kanas::core::image::GetLayout()
{
	return Layout;
}

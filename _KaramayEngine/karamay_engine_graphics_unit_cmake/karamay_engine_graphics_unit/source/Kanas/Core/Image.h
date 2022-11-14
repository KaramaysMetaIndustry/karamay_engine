#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class CommandBuffer;
class Buffer;
class ImageView;

class Image final : public DeviceObject<VkImage>, public std::enable_shared_from_this<Image>
{

	bool Allocate(VkImageType InType, VkFormat InFormat, VkExtent3D InExtent, uint32 InMips, uint32 InLayers, VkSampleCountFlagBits InSamples, VkImageTiling InTileing, VkImageUsageFlags InUsage, VkSharingMode InSharingMode, VkImageLayout InInitalLayout);

	TUniquePtr<DeviceMemory> Mem;

	VkImageLayout Layout;

public:

	Image(Device& InDevice);

	Image(const Device& Other) = delete;
	Image(Device&& Other);

	virtual ~Image() override;

public:

	void CmdClear(CommandBuffer& InRecorder, const VkClearColorValue& InValue, const TVector<VkImageSubresourceRange>& InRanges);

	void CmdClear(CommandBuffer& InRecorder, const VkClearDepthStencilValue& InValue, const TVector<VkImageSubresourceRange>& InRanges);

	void CmdCopy(CommandBuffer& InRecorder, Buffer& InDstBuffer, const TVector<VkBufferImageCopy>& InRegions);

	void CmdCopy(CommandBuffer& InRecorder, Image& InDstImage, const TVector<VkImageCopy>& InRegions);

	void CmdBlit(CommandBuffer& InRecorder, Image& InDstImage, const TVector<VkImageBlit>& InRegions, VkFilter InFilter);

	void CmdResolve(CommandBuffer& InRecorder, Image& InDstImage, const TVector<VkImageResolve>& InRegions);

	VkImageLayout GetLayout();

	TSharedPtr<ImageView> CreateView(VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange);

	const TUniquePtr<DeviceMemory>& GetMemRef() const { return Mem; }


	/*VK_IMAGE_USAGE_TRANSFER_SRC_BIT = 0x00000001,
    VK_IMAGE_USAGE_TRANSFER_DST_BIT = 0x00000002,
    VK_IMAGE_USAGE_SAMPLED_BIT = 0x00000004,
    VK_IMAGE_USAGE_STORAGE_BIT = 0x00000008,
    VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT = 0x00000010,
    VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT = 0x00000020,
    VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT = 0x00000040,
    VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT = 0x00000080,*/
};

// TransferSrc
// TransferDst
// Sampled
// Storage
// ColorAttachment
// DepthStencilAttachment
// TransientAttachment
// InputAttachment

_KANAS_CORE_END

#endif
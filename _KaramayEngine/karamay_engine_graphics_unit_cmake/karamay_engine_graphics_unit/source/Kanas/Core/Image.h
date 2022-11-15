#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FCommandBuffer;
class FBuffer;
class FImageView;

class FImage final : public FDeviceObject<VkImage>, public std::enable_shared_from_this<FImage>
{
	friend class FDevice;

	bool Allocate(VkImageType InType, VkFormat InFormat, VkExtent3D InExtent, uint32 InMips, uint32 InLayers, VkSampleCountFlagBits InSamples, VkImageTiling InTileing, FImageUsage Usage, VkImageLayout InInitalLayout, TSharedPtr<FConcurrentGuide> ConcurrentGuide = nullptr);

public:

	FImage(FDevice& InDevice);

	FImage(const FImage&) = delete;
	FImage(FImage&& Other);

	FImage& operator=(const FImage&) = delete;

	virtual ~FImage() override;

public:

	void CmdClear(FCommandBuffer& InRecorder, const VkClearColorValue& InValue, const TVector<VkImageSubresourceRange>& InRanges);

	void CmdClear(FCommandBuffer& InRecorder, const VkClearDepthStencilValue& InValue, const TVector<VkImageSubresourceRange>& InRanges);

	void CmdCopy(FCommandBuffer& InRecorder, FBuffer& InDstBuffer, const TVector<VkBufferImageCopy>& InRegions);

	void CmdCopy(FCommandBuffer& InRecorder, FImage& InDstImage, const TVector<VkImageCopy>& InRegions);

	void CmdBlit(FCommandBuffer& InRecorder, FImage& InDstImage, const TVector<VkImageBlit>& InRegions, VkFilter InFilter);

	void CmdResolve(FCommandBuffer& InRecorder, FImage& InDstImage, const TVector<VkImageResolve>& InRegions);

private:

	TUniquePtr<FDeviceMemory> Mem;

	VkImageLayout Layout;

public:

	VkImageLayout GetLayout();

	TSharedPtr<FImageView> CreateView(VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange);



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
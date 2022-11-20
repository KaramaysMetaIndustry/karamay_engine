#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class command_buffer;
class buffer;
class image_view;
class device_memory;

class image final : public device_object<VkImage>
{
	friend class device;

	bool alllocate(VkImageType InType, VkFormat InFormat, VkExtent3D InExtent, std::uint32_t InMips, std::uint32_t InLayers, VkSampleCountFlagBits InSamples, VkImageTiling InTileing, imageUsageFlags UsageFlags, VkImageLayout InInitalLayout, std::shared_ptr<FConcurrentGuide> ConcurrentGuide = nullptr);

public:

	image(device& owner);

	image(const image&) = delete;
	image(image&& Other);

	image& operator=(const image&) = delete;

	virtual ~image() override;

public:

	void CmdClear(command_buffer& InRecorder, const VkClearColorValue& InValue, const 
		
		
		
		<VkImageSubresourceRange>& InRanges);

	void CmdClear(command_buffer& InRecorder, const VkClearDepthStencilValue& InValue, const std::vector<VkImageSubresourceRange>& InRanges);

	void CmdCopy(command_buffer& InRecorder, buffer& InDstBuffer, const std::vector<VkBufferImageCopy>& InRegions);

	void CmdCopy(command_buffer& InRecorder, image& InDstImage, const std::vector<VkImageCopy>& InRegions);

	void CmdBlit(command_buffer& InRecorder, image& InDstImage, const std::vector<VkImageBlit>& InRegions, VkFilter InFilter);

	void CmdResolve(command_buffer& InRecorder, image& InDstImage, const std::vector<VkImageResolve>& InRegions);

private:

	std::unique_ptr<device_memory> Mem;

	VkImageLayout Layout;

public:

	VkImageLayout GetLayout();

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
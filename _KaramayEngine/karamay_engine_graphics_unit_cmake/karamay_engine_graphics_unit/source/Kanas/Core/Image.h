#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class CommandBuffer;
class Buffer;
class ImageView;

class Image final : public DeviceObject<VkImage>
{
public:

	Image(Device& InDevice);

	virtual ~Image() override;

public:

	void CmdClear(CommandBuffer& InRecorder, const VkClearColorValue& InValue, const std::vector<VkImageSubresourceRange>& InRanges);

	void CmdClear(CommandBuffer& InRecorder, const VkClearDepthStencilValue& InValue, const std::vector<VkImageSubresourceRange>& InRanges);

	void CmdCopy(CommandBuffer& InRecorder, Buffer& InDstBuffer, const std::vector<VkBufferImageCopy>& InRegions);

	void CmdCopy(CommandBuffer& InRecorder, Image& InDstImage, const std::vector<VkImageCopy>& InRegions);

	void CmdBlit(CommandBuffer& InRecorder, Image& InDstImage, const std::vector<VkImageBlit>& InRegions, VkFilter InFilter);

	void CmdResolve(CommandBuffer& InRecorder, Image& InDstImage, const std::vector<VkImageResolve>& InRegions);

	std::shared_ptr<ImageView> GetView();

};

_KANAS_CORE_END

#endif
#include "Image.h"

Kanas::Core::Image::Image(Device& InDevice) :
	DeviceObject(InDevice)
{
}

Kanas::Core::Image::~Image()
{
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

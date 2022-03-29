#include "image.h"
#include "buffer.h"
#include "pooled_object/command_buffer.h"

image::~image()
{
	vkDestroyImage(_dev.handle(), _handle, nullptr);
}

void image::copy_to(command_buffer& recorder, image& dst, const std::vector<VkImageCopy>& regions)
{
	vkCmdCopyImage(recorder.handle(), _handle, _layout, dst.handle(), dst.layout(), regions.size(), regions.data());
}

void image::copy_to(command_buffer& recorder, buffer& dst, const std::vector<VkBufferImageCopy>& regions)
{
	vkCmdCopyImageToBuffer(recorder.handle(), _handle, _layout, dst.handle(), regions.size(), regions.data());
}

void image::blit_to(command_buffer& recorder, image& dst, const std::vector<VkImageBlit>& regions, VkFilter filter)
{
	vkCmdBlitImage(recorder.handle(), _handle, _layout, dst.handle(), dst.layout(), regions.size(), regions.data(), filter);
}

void image::resolve_to(command_buffer& recorder, image& dst, const std::vector<VkImageResolve>& regions)
{
	vkCmdResolveImage(recorder.handle(), _handle, _layout, dst.handle(), dst.layout(), regions.size(), regions.data());
}

void image::clear(command_buffer& recorder, VkClearColorValue value, const std::vector<VkImageSubresourceRange>& ranges)
{
	vkCmdClearColorImage(recorder.handle(), _handle, _layout, &value, ranges.size(), ranges.data());
}

void image::clear(command_buffer& recorder, VkClearDepthStencilValue value, const std::vector<VkImageSubresourceRange>& ranges)
{
	vkCmdClearDepthStencilImage(recorder.handle(), _handle, _layout, &value, ranges.size(), ranges.data());
}


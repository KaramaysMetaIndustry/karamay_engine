#include "image.h"
#include "buffer.h"
#include "pooled_object/command_buffer.h"

image::image(device& dev) : device_object(dev)
{
}

image::~image()
{
	deallocate();
}

bool image::allocate()
{
	VkImageCreateInfo _create_info;
	_create_info.extent;
	_create_info.imageType;
	_create_info.arrayLayers;
	_create_info.format;
	_create_info.initialLayout;
	_create_info.mipLevels;
	_create_info.pQueueFamilyIndices;
	_create_info.queueFamilyIndexCount;
	_create_info.samples;
	_create_info.sharingMode;
	_create_info.tiling;
	_create_info.usage;

	auto _ret = vkCreateImage(_device.handle(), &_create_info, nullptr, &_handle);

	if (_ret != VkResult::VK_SUCCESS)
	{
		return false;
	}

	return true;
}

void image::deallocate()
{
	if (_handle)
	{
		vkDestroyImage(_device.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

void image::copy_to(command_buffer* recorder, image* dst, const std::vector<VkImageCopy>& regions)
{
	vkCmdCopyImage(recorder->handle(), _handle, _layout, dst->handle(), dst->layout(), regions.size(), regions.data());
}

void image::copy_to(command_buffer* recorder, buffer* dst, const std::vector<VkBufferImageCopy>& regions)
{
	vkCmdCopyImageToBuffer(recorder->handle(), _handle, _layout, dst->handle(), regions.size(), regions.data());
}

void image::blit_to(command_buffer* recorder, image* dst, const std::vector<VkImageBlit>& regions, VkFilter filter)
{
	vkCmdBlitImage(recorder->handle(), _handle, _layout, dst->handle(), dst->layout(), regions.size(), regions.data(), filter);
}

void image::resolve_to(command_buffer* recorder, image* dst, const std::vector<VkImageResolve>& regions)
{
	vkCmdResolveImage(recorder->handle(), _handle, _layout, dst->handle(), dst->layout(), regions.size(), regions.data());
}

void image::clear(command_buffer* recorder, VkClearColorValue value, const std::vector<VkImageSubresourceRange>& ranges)
{
	vkCmdClearColorImage(recorder->handle(), _handle, _layout, &value, ranges.size(), ranges.data());
}

void image::clear(command_buffer* recorder, VkClearDepthStencilValue value, const std::vector<VkImageSubresourceRange>& ranges)
{
	vkCmdClearDepthStencilImage(recorder->handle(), _handle, _layout, &value, ranges.size(), ranges.data());
}

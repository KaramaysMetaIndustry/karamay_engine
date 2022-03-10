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

bool image::allocate(VkFormat format, VkImageType type, uint32 layers, VkExtent3D extent, uint32 mipmaps, VkImageTiling tiling, VkImageUsageFlags usage, VkSharingMode sharing, VkSampleCountFlagBits samples, VkImageLayout layout, const std::vector<uint32>& queue_family_indices)
{
	VkImageCreateInfo _create_info{};
	_create_info.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	_create_info.extent = extent;
	_create_info.imageType = type;
	_create_info.arrayLayers = layers;
	_create_info.format = format;
	_create_info.initialLayout = layout;
	_create_info.mipLevels = mipmaps;
	_create_info.pQueueFamilyIndices = queue_family_indices.data();
	_create_info.queueFamilyIndexCount = queue_family_indices.size();
	_create_info.samples = samples;
	_create_info.sharingMode = sharing;
	_create_info.tiling = tiling;
	_create_info.usage = usage;

	auto _result = vkCreateImage(_device.handle(), &_create_info, nullptr, &_handle);

	if (_result != VkResult::VK_SUCCESS)
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

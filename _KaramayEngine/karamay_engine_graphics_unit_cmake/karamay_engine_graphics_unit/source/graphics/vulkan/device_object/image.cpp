#include "image.h"
#include "buffer.h"
#include "pooled_object/command_buffer.h"

vk_image::~vk_image()
{
	_deallocate();
}

bool vk_image::allocate(const vk_image_parameters& parameters)
{
	if (vkCreateImage(_dev.handle(), &(parameters.core()), nullptr, &_handle) == VkResult::VK_SUCCESS)
	{
		VkMemoryRequirements _requirements{};
		vkGetImageMemoryRequirements(_dev.handle(), _handle, &_requirements);
		_memory = std::make_shared<vk_device_memory>(_dev, _requirements);
		return true;
	}
	return false;
}

std::shared_ptr<vk_image_view> vk_image::create_view() noexcept
{
	return std::shared_ptr<vk_image_view>();
}

void vk_image::copy_to(vk_command_buffer& recorder, vk_image& dst, const std::vector<VkImageCopy>& regions)
{
	vkCmdCopyImage(recorder.handle(), _handle, _layout, dst.handle(), dst.layout(), regions.size(), regions.data());
}

void vk_image::copy_to(vk_command_buffer& recorder, vk_buffer& dst, const std::vector<VkBufferImageCopy>& regions)
{
	vkCmdCopyImageToBuffer(recorder.handle(), _handle, _layout, dst.handle(), regions.size(), regions.data());
}

void vk_image::blit_to(vk_command_buffer& recorder, vk_image& dst, const std::vector<VkImageBlit>& regions, VkFilter filter)
{
	vkCmdBlitImage(recorder.handle(), _handle, _layout, dst.handle(), dst.layout(), regions.size(), regions.data(), filter);
}

void vk_image::resolve_to(vk_command_buffer& recorder, vk_image& dst, const std::vector<VkImageResolve>& regions)
{
	vkCmdResolveImage(recorder.handle(), _handle, _layout, dst.handle(), dst.layout(), regions.size(), regions.data());
}

void vk_image::_deallocate() noexcept
{
	vkDestroyImage(_dev.handle(), _handle, nullptr);
}

void vk_image::clear(vk_command_buffer& recorder, VkClearColorValue value, const std::vector<VkImageSubresourceRange>& ranges)
{
	vkCmdClearColorImage(recorder.handle(), _handle, _layout, &value, ranges.size(), ranges.data());
}

void vk_image::clear(vk_command_buffer& recorder, VkClearDepthStencilValue value, const std::vector<VkImageSubresourceRange>& ranges)
{
	vkCmdClearDepthStencilImage(recorder.handle(), _handle, _layout, &value, ranges.size(), ranges.data());
}

vk_image_view::~vk_image_view() noexcept
{
	_deallocate();
}

bool vk_image_view::allocate(const vk_image_view_parameters& parameters)
{
	if (vkCreateImageView(_dev.handle(), &(parameters.core()), nullptr, &_handle) == VkResult::VK_SUCCESS)
	{

		return true;
	}

	return false;
}

void vk_image_view::_deallocate() noexcept
{
	if (_handle)
	{
		vkDestroyImageView(_dev.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

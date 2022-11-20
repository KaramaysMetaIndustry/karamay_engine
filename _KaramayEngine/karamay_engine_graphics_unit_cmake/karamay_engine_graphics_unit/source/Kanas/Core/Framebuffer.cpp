#include "framebuffer.h"
#include "device.h"
#include "image_view.h"
#include "render_pass.h"

bool kanas::core::framebuffer::alllocate(const render_pass& pass, std::uint32_t width, std::uint32_t height, std::uint32_t layers, const std::vector<std::shared_ptr<image_view>>& image_views)
{
	std::vector<VkImageView> raw_image_views;
	get_raw(image_views, raw_image_views);

	VkFramebufferCreateInfo FramebufferCreateInfo{};
	FramebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	FramebufferCreateInfo.pNext = nullptr;
	FramebufferCreateInfo.flags = {};
	FramebufferCreateInfo.renderPass = pass.get_handle();
	FramebufferCreateInfo.attachmentCount = static_cast<std::uint32_t>(raw_image_views.size());
	FramebufferCreateInfo.pAttachments = raw_image_views.data();
	FramebufferCreateInfo.width = width;
	FramebufferCreateInfo.height = height;
	FramebufferCreateInfo.layers = layers;

	if (vkCreateFramebuffer(get_device().get_handle(), &FramebufferCreateInfo, nullptr, &handle) == VK_SUCCESS)
	{
		attachments = image_views;
		return true;
	}

	return false;
}

kanas::core::framebuffer::framebuffer(device& owner) :
	device_object(owner)
{
}

kanas::core::framebuffer::framebuffer(framebuffer&& Other) :
	device_object(Other.get_device())
{
}

kanas::core::framebuffer::~framebuffer()
{
	if (IsValid())
	{
		vkDestroyFramebuffer(get_device().get_handle(), get_handle(), nullptr);

		reset_handle();
	}
}


#include "framebuffer.h"
#include "image_view.h"
#include "render_pass.h"

framebuffer::framebuffer(device& dev) : device_object(dev)
{
}

framebuffer::~framebuffer()
{
	deallocate();
}

bool framebuffer::allocate(uint32 width, uint32 height, uint32 layers, const std::vector<image_view*>& attachments, render_pass* pass)
{
	VkFramebufferCreateInfo _create_info;
	_create_info.sType;
	_create_info.flags;
	_create_info.width = width;
	_create_info.height = height;
	_create_info.layers = layers;
	_create_info.attachmentCount = attachments.size();
	_create_info.pAttachments;
	_create_info.renderPass = pass->handle();

	vkCreateFramebuffer(_device.handle(), &_create_info, nullptr, &_handle);

	return true;
}

void framebuffer::deallocate()
{
	if (_handle)
	{
		vkDestroyFramebuffer(_device.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

#include "framebuffer.h"
//#include "image_view.h"
#include "render_pass.h"
#include "Framebuffer.h"

void vk_framebuffer::_deallocate()
{
	if (_handle)
	{
		vkDestroyFramebuffer(_dev.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

bool vk_framebuffer::allocate(const vk_framebuffer_parameters& parameters)
{
	vkCreateFramebuffer(_dev.handle(), &(parameters.core()), nullptr, &_handle);
	return true;
}

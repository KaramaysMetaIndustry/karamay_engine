#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "device_object.h"

class vk_framebuffer final : public device_object<VkFramebuffer>
{

	void _deallocate() noexcept;

public:

	vk_framebuffer(vk_device& dev) :
		device_object(dev)
	{}

	~vk_framebuffer() override
	{
		_deallocate();
	}

	bool allocate(const vk_framebuffer_parameters& parameters);

};

#endif
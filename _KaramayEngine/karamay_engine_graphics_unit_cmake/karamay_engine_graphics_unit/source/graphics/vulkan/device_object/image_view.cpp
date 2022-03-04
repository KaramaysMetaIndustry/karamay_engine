#include "image_view.h"
#include "image.h"

image_view::image_view(device& dev) : device_object(dev)
{
}

image_view::~image_view()
{
}

bool image_view::allocate(image* target)
{
	VkImageViewCreateInfo _create_info;
	vkCreateImageView(_device.handle(), &_create_info, nullptr, &_handle);
	return true;
}

void image_view::deallocate()
{
}

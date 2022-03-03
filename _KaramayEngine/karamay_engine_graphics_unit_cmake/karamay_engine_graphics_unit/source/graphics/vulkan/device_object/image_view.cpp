#include "image_view.h"
#include "image.h"

bool image_view::allocate(image* target)
{
	VkImageViewCreateInfo _create_info;
	vkCreateImageView(_device.handle(), &_create_info, nullptr, &_handle);
	return true;
}

void image_view::deallocate()
{
}

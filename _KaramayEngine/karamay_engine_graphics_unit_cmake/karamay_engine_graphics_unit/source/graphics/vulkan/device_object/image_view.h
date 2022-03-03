#ifndef IMAGE_VIEW_H
#define IMAGE_VIEW_H
#include "device_object.h"

class image;

class image_view final : public device_object<VkImageView>
{
private:

	image* _target;

public:

	bool allocate(image* target)
	{
		VkImageViewCreateInfo _create_info;
		vkCreateImageView(_device->handle(), &_create_info, nullptr, &_handle);
		return true;
	}

	void deallocate()
	{

	}

public:



};

#endif
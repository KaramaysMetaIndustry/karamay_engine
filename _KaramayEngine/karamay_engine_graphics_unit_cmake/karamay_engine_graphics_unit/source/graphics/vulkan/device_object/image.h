#ifndef IMAGE_H
#define IMAGE_H
#include "device_object.h"

class command_buffer;

class image final :public device_object<VkImage>
{

public:

	bool allocate()
	{
		VkImageCreateInfo _create_info;
		vkCreateImage(_device->handle(), &_create_info, nullptr, &_handle);

		return true;
	}

	void deallocate()
	{

	}

};

#endif
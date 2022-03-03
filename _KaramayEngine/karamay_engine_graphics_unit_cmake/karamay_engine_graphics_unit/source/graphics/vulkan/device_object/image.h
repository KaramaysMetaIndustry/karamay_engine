#ifndef IMAGE_H
#define IMAGE_H
#include "device_object.h"

class command_buffer;

class image final :public device_object<VkImage>
{

public:

	image(device& dev);

	bool allocate();

	void deallocate();

};

#endif
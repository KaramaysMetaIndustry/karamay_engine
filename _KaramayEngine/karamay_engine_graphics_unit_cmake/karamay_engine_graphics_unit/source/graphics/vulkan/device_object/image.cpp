#include "image.h"

image::image(device& dev) : device_object(dev)
{
}

bool image::allocate()
{
	return false;
}

void image::deallocate()
{
}

#ifndef DEIVCE_OBJECT_H
#define DEIVCE_OBJECT_H
#include "graphics/vulkan/device.h"

template<typename vk_handle_t>
class device_object : public vulkan_object<vk_handle_t>
{
protected:

	// device object lifecycle < device
	device& _device;

public:

	device_object(device& dev) : _device(dev) {}

	~device_object() override {}

};


#endif

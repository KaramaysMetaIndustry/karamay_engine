#ifndef DEIVCE_OBJECT_H
#define DEIVCE_OBJECT_H
#include "graphics/vulkan/device.h"

template<typename vk_handle_t>
class device_object : public vulkan_object<vk_handle_t>
{

protected:

	// device object lifecycle < device
	device& _dev;

public:

	device_object(device& dev) : _dev(dev) {}

	device_object(const device_object&) = delete;
	device_object& operator=(const device_object&) = delete;

	~device_object() override {}

public:

	bool is_valid() const noexcept override 
	{ 
		return vulkan_object<vk_handle_t>::is_valid() && true; 
	}

};


#endif

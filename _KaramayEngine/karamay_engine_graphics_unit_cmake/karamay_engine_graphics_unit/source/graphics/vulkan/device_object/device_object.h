#ifndef DEIVCE_OBJECT_H
#define DEIVCE_OBJECT_H
#include "graphics/vulkan/vulkan_object.h"

template<typename vk_handle_t>
class device_object : public vulkan_object<vk_handle_t>
{
public:

	device_object() = default;

};


#endif

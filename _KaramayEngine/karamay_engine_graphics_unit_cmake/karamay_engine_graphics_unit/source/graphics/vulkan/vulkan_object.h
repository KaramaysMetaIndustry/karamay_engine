#ifndef VULKAN_OBJECT_H
#define VULKAN_OBJECT_H
#include "public/stl.h"
#include "public/vulkan_core.h"

template<typename vk_handle_t>
class vulkan_object
{
protected:

	vk_handle_t _handle = {};

public:

	vk_handle_t handle() const noexcept { return _handle; }

public:

	vulkan_object() = default;

	virtual ~vulkan_object() = default;

};

#endif
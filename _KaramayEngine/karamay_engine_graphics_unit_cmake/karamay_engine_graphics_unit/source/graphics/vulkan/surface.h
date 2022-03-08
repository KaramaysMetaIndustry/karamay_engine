#ifndef SURFACE_H
#define SURFACE_H
#include "device_object/device_object.h"
#include "graphics/vulkan/instance.h"
#include "public/glfw.h"

class surface final : public device_object<VkSurfaceKHR>
{
private:

	instance& _instance;

public:

	bool allocate()
	{
		glfwCreateWindowSurface(_instance.handle(), nullptr, nullptr, &_handle);
	}

	void deallocate() noexcept
	{
		vkDestroySurfaceKHR({}, _handle, nullptr);
	}

};

#endif
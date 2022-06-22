#ifndef RENDERER_H
#define RENDERER_H
#include "graphics/vulkan/instance.h"
#include "graphics/vulkan/device.h"
#include "graphics/vulkan/device_object/buffer.h"
#include "graphics/vulkan/device_object/render_pass.h"
#include "graphics/vulkan/device_object/pooled_object/command_pool.h"
#include "graphics/vulkan/device_object/pooled_object/command_buffer.h"
#include "graphics/vulkan/device_object/framebuffer.h"
#include "graphics/vulkan/device_object/queue.h"

class vk_renderer
{
	std::unordered_map<std::string, std::shared_ptr<vk_render_pass>> passes;

protected:

	vk_device& _device;

public:

	vk_renderer(vk_device& dev) :
		_device(dev)
	{}

	vk_renderer(const vk_renderer&) = delete;
	vk_renderer& operator=(const vk_renderer&) = delete;

	~vk_renderer()
	{
	}

public:

	virtual void render(float delta_time) noexcept = 0;

};

#endif
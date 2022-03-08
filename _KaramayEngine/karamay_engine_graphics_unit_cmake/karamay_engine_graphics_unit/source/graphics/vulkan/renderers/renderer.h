#ifndef RENDERER_H
#define RENDERER_H
#include "graphics/vulkan/instance.h"
#include "graphics/vulkan/device.h"
#include "graphics/vulkan/device_object/buffer.h"
#include "graphics/vulkan/device_object/render_pass.h"
#include "graphics/vulkan/device_object/command_pool.h"
#include "graphics/vulkan/device_object/pooled_object/command_buffer.h"
#include "graphics/vulkan/device_object/framebuffer.h"
#include "graphics/vulkan/device_object/queue.h"

class renderer
{
public:

	renderer(device& dev);

	renderer(const renderer&) = delete;
	renderer& operator=(const renderer&) = delete;

	~renderer();

protected:

    device& _device;

public:

	virtual bool allocate(device* dev) noexcept;

	virtual void render(float delta_time) noexcept;

	virtual void deallocate() noexcept;

};

#endif
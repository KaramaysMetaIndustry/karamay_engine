#ifndef RENDER_PASS_H
#define RENDER_PASS_H
#include "device_object.h"

class vk_command_buffer;

class vk_render_pass final : public device_object<VkRenderPass>
{
	void _deallocate();

public:

	vk_render_pass(vk_device& dev) : 
		device_object(dev)
	{}

	vk_render_pass(const vk_render_pass&) = delete;
	vk_render_pass& operator=(const vk_render_pass&) = delete;

	~vk_render_pass() override
	{
		_deallocate();
	}

	bool allocate(
		const std::vector<VkAttachmentDescription>& attachments, 
		const std::vector<VkSubpassDependency>& dependencies, 
		const std::vector<VkSubpassDescription>& subpasses
	);

private:

	void _begin(vk_command_buffer* recorder, vk_framebuffer* render_target, const std::vector<VkClearValue>& clear_values, VkRect2D render_area, VkSubpassContents contents);

	void _end(vk_command_buffer* recorder);

public:

	void set(const std::function<void(vk_framebuffer*, vk_command_buffer*)>& sequence);

};

#endif
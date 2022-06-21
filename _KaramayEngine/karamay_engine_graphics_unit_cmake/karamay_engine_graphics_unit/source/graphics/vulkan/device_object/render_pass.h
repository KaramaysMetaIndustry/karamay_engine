#ifndef RENDER_PASS_H
#define RENDER_PASS_H
#include "device_object.h"

class command_buffer;

class vk_render_pass final : public device_object<VkRenderPass>
{
public:

	vk_render_pass(vk_device& dev);

	vk_render_pass(const vk_render_pass&) = delete;
	vk_render_pass& operator=(const vk_render_pass&) = delete;

	~vk_render_pass() override;

public:

	bool allocate(
		const std::vector<VkAttachmentDescription>& attachments, 
		const std::vector<VkSubpassDependency>& dependencies, 
		const std::vector<VkSubpassDescription>& subpasses
	);

	void deallocate();

public:

	void set(const std::function<void(framebuffer*, vk_command_buffer*)>& sequence);

private:

	void _begin(vk_command_buffer* recorder, framebuffer* render_target, const std::vector<VkClearValue>& clear_values, VkRect2D render_area, VkSubpassContents contents);
		   
	void _end(vk_command_buffer* recorder);

};

#endif
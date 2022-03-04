#ifndef RENDER_PASS_H
#define RENDER_PASS_H
#include "device_object.h"

class command_buffer;

class render_pass final : public device_object<VkRenderPass>
{
public:

	render_pass(device& dev);

	render_pass(const render_pass&) = delete;
	render_pass& operator=(const render_pass&) = delete;

	~render_pass() override;

public:

	bool allocate(
		const std::vector<VkAttachmentDescription>& attachments, 
		const std::vector<VkSubpassDependency>& dependencies, 
		const std::vector<VkSubpassDescription>& subpasses
	);

	void deallocate();

public:

	void set(const std::function<void(framebuffer*, command_buffer*)>& sequence);

private:

	void _begin(command_buffer* recorder, framebuffer* render_target, const std::vector<VkClearValue>& clear_values, VkRect2D render_area, VkSubpassContents contents);
		   
	void _end(command_buffer* recorder);

};

#endif
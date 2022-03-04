#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "device_object.h"

class framebuffer final : public device_object<VkFramebuffer>
{
public:

	framebuffer(device& dev);

	~framebuffer() override;

public:

	bool allocate(uint32 width, uint32 height, uint32 layers, const std::vector<image_view*>& attachments, render_pass* pass);

	void deallocate();

};

#endif
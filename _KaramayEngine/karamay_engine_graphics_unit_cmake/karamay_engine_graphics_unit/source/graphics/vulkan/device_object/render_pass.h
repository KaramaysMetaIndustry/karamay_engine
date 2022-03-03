#ifndef RENDER_PASS_H
#define RENDER_PASS_H
#include "device_object.h"

class render_pass final : public device_object<VkRenderPass>
{
public:

	render_pass(device& dev);

	~render_pass() override;

public:

	bool allocate();

	void deallocate();

};

#endif
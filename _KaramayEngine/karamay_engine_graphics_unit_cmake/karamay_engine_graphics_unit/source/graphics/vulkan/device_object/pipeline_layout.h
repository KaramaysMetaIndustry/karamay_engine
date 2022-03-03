#ifndef PIPELINE_LAYOUT_H
#define PIPELINE_LAYOUT_H
#include "device_object.h"

class pipeline_layout final : public device_object<VkPipelineLayout>
{
public:

	pipeline_layout(device& dev);

	~pipeline_layout() override;

public:

	bool allocate();

	void deallocate();

};

#endif
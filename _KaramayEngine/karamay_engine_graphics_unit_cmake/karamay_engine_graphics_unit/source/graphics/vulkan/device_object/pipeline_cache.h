#ifndef PIPELINE_CACHE_H
#define PIPELINE_CACHE_H
#include "device_object.h"

class pipeline_cache final : public device_object<VkPipelineCache>
{
public:

	pipeline_cache(device& dev);

	~pipeline_cache() override;

public:

	bool allocate(uint64 size, void* data);

	void deallocate();

};

#endif
#ifndef PIPELINE_CACHE_H
#define PIPELINE_CACHE_H
#include "device_object.h"

class pipeline_cache final : public device_object<VkPipelineCache>
{
public:

	pipeline_cache(device& dev);

	pipeline_cache(const pipeline_cache&) = delete;
	pipeline_cache& operator=(const pipeline_cache&) = delete;

	~pipeline_cache() override;

public:

	bool allocate(uint64 size, void* data) noexcept;

	void deallocate() noexcept;

public:

	bool fetch(uint64 size, void* data) const noexcept;

	bool merge(const std::vector<pipeline_cache*>& caches) noexcept;

};

#endif
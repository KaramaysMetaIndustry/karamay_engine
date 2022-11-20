#ifndef _PIPELINE_CACHE_H_
#define _PIPELINE_CACHE_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class pipeline_cache final : public device_object<VkPipelineCache>
{
public:

	pipeline_cache(device& owner);

	virtual ~pipeline_cache() override;

	bool alllocate();

	bool alllocate(const std::vector<uint8>& InCacheData);

	void GetCacheData(std::vector<uint8>& OutData);

	std::uint64_t GetCacheDataSize() const;

};

_KANAS_CORE_END

#endif
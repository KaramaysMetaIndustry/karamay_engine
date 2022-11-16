#ifndef _PIPELINE_CACHE_H_
#define _PIPELINE_CACHE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FPipelineCache final : public FDeviceObject<VkPipelineCache>
{
public:

	FPipelineCache(FDevice& InDevice);

	virtual ~FPipelineCache() override;

	bool Allocate();

	bool Allocate(const std::vector<uint8>& InCacheData);

	void GetCacheData(std::vector<uint8>& OutData);

	uint64 GetCacheDataSize() const;

};

_KANAS_CORE_END

#endif
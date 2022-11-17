#include "PipelineCache.h"
#include "Device.h"

Kanas::Core::FPipelineCache::FPipelineCache(FDevice& InDevice) :
    FDeviceObject(InDevice)
{
}

Kanas::Core::FPipelineCache::~FPipelineCache()
{
    if (IsValid())
    {
        vkDestroyPipelineCache(GetDevice().GetHandle(), GetHandle(), nullptr);
        
        ResetHandle();
    }
}

bool Kanas::Core::FPipelineCache::Allocate()
{
    VkPipelineCacheCreateInfo _PipelineCacheCreateInfo;
    _PipelineCacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    _PipelineCacheCreateInfo.pNext = nullptr;
    _PipelineCacheCreateInfo.flags;
    _PipelineCacheCreateInfo.initialDataSize = 0;
    _PipelineCacheCreateInfo.pInitialData = nullptr;

    VkResult _Result = vkCreatePipelineCache(GetDevice().GetHandle(), &_PipelineCacheCreateInfo, nullptr, &_Handle);

    if (_Result == VkResult::VK_SUCCESS)
    {
        return true;
    }

    return false;
}

bool Kanas::Core::FPipelineCache::Allocate(const std::vector<uint8>& InCacheData)
{
    VkPipelineCacheCreateInfo _PipelineCacheCreateInfo;
    _PipelineCacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    _PipelineCacheCreateInfo.pNext = nullptr;
    _PipelineCacheCreateInfo.flags;
    _PipelineCacheCreateInfo.initialDataSize = InCacheData.size();
    _PipelineCacheCreateInfo.pInitialData = InCacheData.data();

    VkResult _Result = vkCreatePipelineCache(GetDevice().GetHandle(), &_PipelineCacheCreateInfo, nullptr, &_Handle);

    if (_Result == VkResult::VK_SUCCESS)
    {
        return true;
    }

    return false;
}

void Kanas::Core::FPipelineCache::GetCacheData(std::vector<uint8>& OutData)
{
    const uint64 CacheDataSize = GetCacheDataSize();
    OutData.resize(CacheDataSize);
	vkGetPipelineCacheData(GetDevice().GetHandle(), _Handle, nullptr, OutData.data());
}

uint64 Kanas::Core::FPipelineCache::GetCacheDataSize() const
{
    uint64 CacheDataSize = 0;
    vkGetPipelineCacheData(GetDevice().GetHandle(), _Handle, &CacheDataSize, nullptr);
    return CacheDataSize;
}
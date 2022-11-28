#include "pipeline_cache.h"
#include "device.h"

kanas::core::pipeline_cache::pipeline_cache(device& owner) :
    device_object(owner)
{
}

kanas::core::pipeline_cache::~pipeline_cache()
{
    if (IsValid())
    {
        vkDestroypipeline_cache(get_device().get_handle(), get_handle(), nullptr);
        
        reset_handle();
    }
}

bool kanas::core::pipeline_cache::alllocate()
{
    Vkpipeline_cacheCreateInfo _pipeline_cacheCreateInfo;
    _pipeline_cacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    _pipeline_cacheCreateInfo.pNext = nullptr;
    _pipeline_cacheCreateInfo.flags;
    _pipeline_cacheCreateInfo.initialDataSize = 0;
    _pipeline_cacheCreateInfo.pInitialData = nullptr;

    VkResult _Result = vkCreatepipeline_cache(get_device().get_handle(), &_pipeline_cacheCreateInfo, nullptr, &handle);

    if (_Result == VkResult::VK_SUCCESS)
    {
        return true;
    }

    return false;
}

bool kanas::core::pipeline_cache::alllocate(const std::vector<uint8>& InCacheData)
{
    Vkpipeline_cacheCreateInfo _pipeline_cacheCreateInfo;
    _pipeline_cacheCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
    _pipeline_cacheCreateInfo.pNext = nullptr;
    _pipeline_cacheCreateInfo.flags;
    _pipeline_cacheCreateInfo.initialDataSize = InCacheData.size();
    _pipeline_cacheCreateInfo.pInitialData = InCacheData.data();

    VkResult _Result = vkCreatepipeline_cache(get_device().get_handle(), &_pipeline_cacheCreateInfo, nullptr, &handle);

    if (_Result == VkResult::VK_SUCCESS)
    {
        return true;
    }

    return false;
}

void kanas::core::pipeline_cache::GetCacheData(std::vector<uint8>& OutData)
{
    const std::uint64_t CacheDataSize = GetCacheDataSize();
    OutData.resize(CacheDataSize);
	vkGetpipeline_cacheData(get_device().get_handle(), handle, nullptr, OutData.data());
}

std::uint64_t kanas::core::pipeline_cache::GetCacheDataSize() const
{
    std::uint64_t CacheDataSize = 0;
    vkGetpipeline_cacheData(get_device().get_handle(), handle, &CacheDataSize, nullptr);
    return CacheDataSize;
}

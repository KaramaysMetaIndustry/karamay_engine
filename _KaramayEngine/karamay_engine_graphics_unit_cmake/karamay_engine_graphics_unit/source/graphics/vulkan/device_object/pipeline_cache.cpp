#include "pipeline_cache.h"

pipeline_cache::pipeline_cache(device& dev) : device_object(dev)
{
}

pipeline_cache::~pipeline_cache()
{
    deallocate();
}

bool pipeline_cache::allocate(uint64 size, void* data) noexcept
{
    if (!data || size < 1) return false;

    VkPipelineCacheCreateInfo _create_info;
    _create_info.sType;
    _create_info.initialDataSize = size;
    _create_info.pInitialData = data;
    _create_info.flags;

    auto _ret = vkCreatePipelineCache(_dev.handle(), &_create_info, nullptr, &_handle);
    if (_ret != VkResult::VK_SUCCESS)
    {
        return false;
    }

    return true;
}

void pipeline_cache::deallocate() noexcept
{
    if (_handle)
    {
        vkDestroyPipelineCache(_dev.handle(), _handle, nullptr);
        _handle = nullptr;
    }
}

bool pipeline_cache::fetch(uint64 size, void* data) const noexcept
{
    vkGetPipelineCacheData(_dev.handle(), _handle, &size, data);
    return true;
}

bool pipeline_cache::merge(const std::vector<pipeline_cache*>& caches) noexcept
{
    std::vector<VkPipelineCache> _caches(caches.size());
    for (auto cache : caches)
    {
        _caches.push_back(cache->handle());
    }

    vkMergePipelineCaches(_dev.handle(), _handle, _caches.size(), _caches.data());
    return true;
}

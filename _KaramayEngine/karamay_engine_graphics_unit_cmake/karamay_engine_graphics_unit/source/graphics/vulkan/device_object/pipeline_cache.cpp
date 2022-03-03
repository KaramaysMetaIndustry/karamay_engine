#include "pipeline_cache.h"

pipeline_cache::pipeline_cache(device& dev) : device_object(dev)
{
}

pipeline_cache::~pipeline_cache()
{
    deallocate();
}

bool pipeline_cache::allocate(uint64 size, void* data)
{
    if (!data || size < 1) return false;

    VkPipelineCacheCreateInfo _create_info;
    _create_info.sType;
    _create_info.initialDataSize = size;
    _create_info.pInitialData = data;
    _create_info.flags;

    auto _ret = vkCreatePipelineCache(_device.handle(), &_create_info, nullptr, &_handle);
    if (_ret != VkResult::VK_SUCCESS)
    {
        return false;
    }

    return true;
}

void pipeline_cache::deallocate()
{
    vkDestroyPipelineCache(_device.handle(), _handle, nullptr);
    _handle = nullptr;
}

#include "query_pool.h"
#include "pooled_object/command_buffer.h"
#include "buffer.h"

query_pool::query_pool(device& dev) : device_object(dev)
{
}

query_pool::~query_pool()
{
    deallocate();
}

bool query_pool::allocate(VkQueryType type, uint32 count, VkQueryPipelineStatisticFlags flags)
{
    VkQueryPoolCreateInfo _create_info;
    _create_info.sType = VK_STRUCTURE_TYPE_QUERY_POOL_CREATE_INFO;
    _create_info.flags;
    _create_info.queryType = type;
    _create_info.queryCount = count;
    _create_info.pipelineStatistics = flags;

    vkCreateQueryPool(_dev.handle(), &_create_info, nullptr, &_handle);

    return true;
}

void query_pool::deallocate()
{
    if (_handle)
    {
        vkDestroyQueryPool(_dev.handle(), _handle, nullptr);
        _handle = nullptr;
    }
}

void query_pool::reset(command_buffer* recorder, uint32 first_query, uint32 query_count)
{
    vkCmdResetQueryPool(recorder->handle(), _handle, first_query, query_count);
}

void query_pool::copy_results(command_buffer* recorder, uint32 first_query, uint32 query_count, buffer* dst, uint64 offset, uint64 stride, VkQueryResultFlags flags)
{
    vkCmdCopyQueryPoolResults(recorder->handle(), _handle, first_query, query_count, dst->handle(), offset, stride, flags);
}

void query_pool::begin(command_buffer* recorder, uint32 index, VkQueryControlFlags flags)
{
    vkCmdBeginQuery(recorder->handle(), _handle,index, flags);
}

void query_pool::end(command_buffer* recorder, uint32 index)
{
    vkCmdEndQuery(recorder->handle(), _handle, index);
}

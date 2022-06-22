#include "query_pool.h"
#include "pooled_object/command_buffer.h"
#include "buffer.h"

void vk_query_pool::_deallocate()
{
    if (_handle)
    {
        vkDestroyQueryPool(_dev.handle(), _handle, nullptr);
        _handle = nullptr;
    }
}

bool vk_query_pool::allocate(const vk_query_pool_parameters& parameters)
{
    vkCreateQueryPool(_dev.handle(), &(parameters.core()), nullptr, &_handle);
    return true;
}

void vk_query_pool::reset(vk_command_buffer* recorder, uint32 first_query, uint32 query_count)
{
    vkCmdResetQueryPool(recorder->handle(), _handle, first_query, query_count);
}

void vk_query_pool::copy_results(vk_command_buffer* recorder, uint32 first_query, uint32 query_count, vk_buffer* dst, uint64 offset, uint64 stride, VkQueryResultFlags flags)
{
    vkCmdCopyQueryPoolResults(recorder->handle(), _handle, first_query, query_count, dst->handle(), offset, stride, flags);
}

void vk_query_pool::begin(vk_command_buffer* recorder, uint32 index, VkQueryControlFlags flags)
{
    vkCmdBeginQuery(recorder->handle(), _handle,index, flags);
}

void vk_query_pool::end(vk_command_buffer* recorder, uint32 index)
{
    vkCmdEndQuery(recorder->handle(), _handle, index);
}

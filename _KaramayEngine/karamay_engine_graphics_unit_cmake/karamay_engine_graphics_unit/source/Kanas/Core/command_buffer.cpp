#include "command_buffer.h"
#include "command_pool.h"
#include "render_pass.h"
#include "subpass.h"
#include "framebuffer.h"
#include "device.h"

bool kanas::core::command_buffer::alllocate(command_buffer_level level)
{
    VkCommandBufferAllocateInfo CommandBufferalllocateInfo;
    CommandBufferalllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    CommandBufferalllocateInfo.commandBufferCount = 1;
    CommandBufferalllocateInfo.commandPool = _pool.get_handle();
    CommandBufferalllocateInfo.level = static_cast<VkCommandBufferLevel>(level);

    VkResult Result = vkAllocateCommandBuffers(get_device().get_handle(), &CommandBufferalllocateInfo, &handle);

    if (Result == VkResult::VK_SUCCESS)
    {
        return true;
    }

    return false;
}

kanas::core::command_buffer::command_buffer(device& owner,command_pool& pool) :
    device_object(owner), 
    _pool(pool)
{
}

kanas::core::command_buffer::~command_buffer()
{
    if (IsValid())
    {
        vkFreeCommandBuffers(get_device().get_handle(), _pool.get_handle(), 1, &handle);

        reset_handle();
    }
}

void kanas::core::command_buffer::cmd_barrier()
{
    VkMemoryBarrier MemoryBarriers[1] = {};
    VkBufferMemoryBarrier BufferMemoryBarriers[1] = {};
    VkImageMemoryBarrier ImageMemoryBarriers[1] = {};

    VkPipelineStageFlags InSrcStageMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;
    VkPipelineStageFlags InDstStageMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
    VkDependencyFlags DependencyFlags = VkDependencyFlagBits::VK_DEPENDENCY_BY_REGION_BIT;

    vkCmdPipelineBarrier(get_handle(), InSrcStageMask, InDstStageMask, DependencyFlags, 1, MemoryBarriers, 1, BufferMemoryBarriers, 1, ImageMemoryBarriers);
}

bool kanas::core::command_buffer::reset(command_buffer_reset_flags flags)
{
    return vkResetCommandBuffer(get_handle(), flags.get()) == VK_SUCCESS;
}

kanas::core::primary_command_buffer::primary_command_buffer()
{
}

kanas::core::primary_command_buffer::~primary_command_buffer()
{
}

bool kanas::core::primary_command_buffer::record(std::shared_ptr<render_pass> pass)
{
    if (!pass)
    {
        return false;
    }

    VkCommandBufferBeginInfo CommandBufferBeginInfo{};
    CommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    CommandBufferBeginInfo.pNext = nullptr;
    CommandBufferBeginInfo.flags = command_buffer_usage_flags().set_one_time_submit().get();
    CommandBufferBeginInfo.pInheritanceInfo = nullptr;

    if (vkBeginCommandBuffer(get_handle(), &CommandBufferBeginInfo) != VK_SUCCESS)
    {
        return false;
    }

    pass->cmd_execute(*this);

    if (vkEndCommandBuffer(get_handle()) != VK_SUCCESS)
    {
        return false;
    }

    return true;
}

kanas::core::secondary_command_buffer::secondary_command_buffer()
{
}

kanas::core::secondary_command_buffer::~secondary_command_buffer()
{
}

bool kanas::core::secondary_command_buffer::record(subpass& pass)
{
    VkCommandBufferInheritanceInfo CommandBufferInheritanceInfo;
    CommandBufferInheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
    CommandBufferInheritanceInfo.pNext = nullptr;
    CommandBufferInheritanceInfo.renderPass = pass.get_render_pass()->get_handle();
    CommandBufferInheritanceInfo.subpass = pass.get_index();
    CommandBufferInheritanceInfo.framebuffer = pass.get_render_pass()->render_target()->get_handle();
    CommandBufferInheritanceInfo.occlusionQueryEnable = false;
    CommandBufferInheritanceInfo.queryFlags = query_control_flags().set_precise(); 
    CommandBufferInheritanceInfo.pipelineStatistics = FQueryPipelineStatisticFlags().SetGeometryShaderInvocations().Get();

    VkCommandBufferBeginInfo CommandBufferBeginInfo;
    CommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    CommandBufferBeginInfo.pNext = nullptr;
    CommandBufferBeginInfo.flags = command_bufferUsageFlags().SetRenderPassContinue().Get();
    CommandBufferBeginInfo.pInheritanceInfo = &CommandBufferInheritanceInfo;

    if(vkBeginCommandBuffer(get_handle(), &CommandBufferBeginInfo) != VK_SUCCESS)
    {
        return false;
    }

    pass.cmd_execute(*this);

    if (vkEndCommandBuffer(get_handle()) != VK_SUCCESS)
    {
        return false;
    }

    return  true;
}
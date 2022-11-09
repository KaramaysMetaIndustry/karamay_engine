#include "CommandBuffer.h"
#include "CommandPool.h"
#include "Device.h"
#include "RenderPass.h"
#include "Framebuffer.h"

bool Kanas::Core::CommandBuffer::Allocate(CommandBuffeLevel InCommandBufferLevel)
{
    VkCommandBufferAllocateInfo CommandBufferAllocateInfo;
    CommandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    CommandBufferAllocateInfo.commandBufferCount = 1;
    CommandBufferAllocateInfo.commandPool = Pool.GetHandle();
    CommandBufferAllocateInfo.level = static_cast<VkCommandBufferLevel>(InCommandBufferLevel);

    VkResult Result = vkAllocateCommandBuffers(GetDevice().GetHandle(), &CommandBufferAllocateInfo, &_Handle);

    if (Result == VkResult::VK_SUCCESS)
    {
        return true;
    }

    return false;
}

Kanas::Core::CommandBuffer::CommandBuffer(Device& InDevice, CommandPool& InCommandPool) :
    DeviceObject(InDevice), Pool(InCommandPool)
{
}

Kanas::Core::CommandBuffer::~CommandBuffer()
{
    if (IsValid())
    {
        vkFreeCommandBuffers(GetDevice().GetHandle(), Pool.GetHandle(), 1, &_Handle);

        ResetHandle();
    }
}

void Kanas::Core::CommandBuffer::CmdBarrier()
{
    VkMemoryBarrier MemoryBarriers[1] = {};
    VkBufferMemoryBarrier BufferMemoryBarriers[1] = {};
    VkImageMemoryBarrier ImageMemoryBarriers[1] = {};

    VkPipelineStageFlags InSrcStageMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;
    VkPipelineStageFlags InDstStageMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
    VkDependencyFlags DependencyFlags = VkDependencyFlagBits::VK_DEPENDENCY_BY_REGION_BIT;

    vkCmdPipelineBarrier(GetHandle(), InSrcStageMask, InDstStageMask, DependencyFlags, 1, MemoryBarriers, 1, BufferMemoryBarriers, 1, ImageMemoryBarriers);
}

void Kanas::Core::CommandBuffer::CmdExecute()
{
    VkCommandBuffer CommandBufferHandles[] = { GetHandle() };
    vkCmdExecuteCommands(GetHandle(), 1, CommandBufferHandles);
}

void Kanas::Core::CommandBuffer::CmdPush(RenderPass* InRenderPass, uint32 InSubpassIndex, bool InOcclusionQueryEnable, VkQueryControlFlags InQueryControlFlags, VkQueryPipelineStatisticFlags InQueryPipelineStatisticFlags)
{
    if (!InRenderPass)
    {
        return;
    }

    VkCommandBufferInheritanceInfo CommandBufferInheritanceInfo;
    CommandBufferInheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
    CommandBufferInheritanceInfo.pNext = nullptr;
    CommandBufferInheritanceInfo.renderPass = InRenderPass->GetHandle();
    CommandBufferInheritanceInfo.subpass = InSubpassIndex;
    CommandBufferInheritanceInfo.framebuffer = InRenderPass->GetFramebuffer()->GetHandle();
    CommandBufferInheritanceInfo.occlusionQueryEnable = InOcclusionQueryEnable;
    CommandBufferInheritanceInfo.queryFlags = InQueryControlFlags;
    CommandBufferInheritanceInfo.pipelineStatistics = InQueryPipelineStatisticFlags;

    VkCommandBufferBeginInfo CommandBufferBeginInfo;
    CommandBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    CommandBufferBeginInfo.pNext = nullptr;
    CommandBufferBeginInfo.flags = {};
    CommandBufferBeginInfo.pInheritanceInfo = &CommandBufferInheritanceInfo;
    
    VkResult Result = VkResult::VK_SUCCESS;

    Result = vkBeginCommandBuffer(GetHandle(), &CommandBufferBeginInfo);

    InRenderPass->CmdCollect(*this);
    
    Result = vkEndCommandBuffer(GetHandle());
}

VkResult Kanas::Core::CommandBuffer::Reset(VkCommandBufferResetFlags InResetFlags)
{
    return vkResetCommandBuffer(GetHandle(), InResetFlags);
}

Kanas::Core::CommandPool& Kanas::Core::CommandBuffer::GetPool()
{
    return Pool;
}


#include "CommandBuffer.h"
#include "CommandPool.h"
#include "Device.h"
#include "RenderPass.h"
#include "Framebuffer.h"

bool Kanas::Core::FCommandBuffer::Allocate(ECommandBuffeLevel InCommandBufferLevel)
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

Kanas::Core::FCommandBuffer::FCommandBuffer(FDevice& InDevice,FCommandPool& InCommandPool) :
    FDeviceObject(InDevice), Pool(InCommandPool)
{
}

Kanas::Core::FCommandBuffer::~FCommandBuffer()
{
    if (IsValid())
    {
        vkFreeCommandBuffers(GetDevice().GetHandle(), Pool.GetHandle(), 1, &_Handle);

        ResetHandle();
    }
}

void Kanas::Core::FCommandBuffer::CmdBarrier()
{
    VkMemoryBarrier MemoryBarriers[1] = {};
    VkBufferMemoryBarrier BufferMemoryBarriers[1] = {};
    VkImageMemoryBarrier ImageMemoryBarriers[1] = {};

    VkPipelineStageFlags InSrcStageMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT;
    VkPipelineStageFlags InDstStageMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT;
    VkDependencyFlags DependencyFlags = VkDependencyFlagBits::VK_DEPENDENCY_BY_REGION_BIT;

    vkCmdPipelineBarrier(GetHandle(), InSrcStageMask, InDstStageMask, DependencyFlags, 1, MemoryBarriers, 1, BufferMemoryBarriers, 1, ImageMemoryBarriers);
}

void Kanas::Core::FCommandBuffer::CmdExecute()
{
    VkCommandBuffer CommandBufferHandles[] = { GetHandle() };
    vkCmdExecuteCommands(GetHandle(), 1, CommandBufferHandles);
}

void Kanas::Core::FCommandBuffer::CmdPush(FRenderPass* InRenderPass, uint32 InSubpassIndex, bool InOcclusionQueryEnable, VkQueryControlFlags InQueryControlFlags, VkQueryPipelineStatisticFlags InQueryPipelineStatisticFlags)
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

VkResult Kanas::Core::FCommandBuffer::Reset(VkCommandBufferResetFlags InResetFlags)
{
    return vkResetCommandBuffer(GetHandle(), InResetFlags);
}

Kanas::Core::FCommandPool& Kanas::Core::FCommandBuffer::GetPool()
{
    return Pool;
}


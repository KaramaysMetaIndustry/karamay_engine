#include "CommandBuffer.h"
#include "CommandPool.h"
#include "Device.h"
#include "RenderPass.h"
#include "Framebuffer.h"

Kanas::Core::CommandBuffer::CommandBuffer(Device& InDevice, CommandPool& InCommandPool) :
    DeviceObject(InDevice), Pool(InCommandPool)
{
}

Kanas::Core::CommandBuffer::~CommandBuffer()
{
    if (_Handle != VK_NULL_HANDLE)
    {
        vkFreeCommandBuffers(GetDevice().GetHandle(), Pool.GetHandle(), 1, &_Handle);
        _Handle = VK_NULL_HANDLE;
    }
}

Kanas::Core::CommandPool& Kanas::Core::CommandBuffer::GetPool()
{
    return Pool;
}

bool Kanas::Core::CommandBuffer::Allocate(VkCommandBufferLevel InCommandBufferLevel)
{
    VkCommandBufferAllocateInfo CommandBufferAllocateInfo;
    CommandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    CommandBufferAllocateInfo.commandBufferCount = 1;
    CommandBufferAllocateInfo.commandPool = Pool.GetHandle();
    CommandBufferAllocateInfo.level = InCommandBufferLevel;

    VkResult Result = vkAllocateCommandBuffers(GetDevice().GetHandle(), &CommandBufferAllocateInfo, &_Handle);
    if (Result == VkResult::VK_SUCCESS)
    {
        return true;
    }

    return false;
}

void Kanas::Core::CommandBuffer::Reset(VkCommandBufferResetFlags InResetFlags)
{
    const VkResult Result = vkResetCommandBuffer(_Handle, InResetFlags);
}

void Kanas::Core::CommandBuffer::Push(RenderPass* InRenderPass, uint32 InSubpassIndex, bool InOcclusionQueryEnable, VkQueryControlFlags InQueryControlFlags, VkQueryPipelineStatisticFlags InQueryPipelineStatisticFlags)
{
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
    CommandBufferBeginInfo.flags;
    CommandBufferBeginInfo.pInheritanceInfo = &CommandBufferInheritanceInfo;
    
    vkBeginCommandBuffer(_Handle, &CommandBufferBeginInfo);

    InRenderPass->CmdCollect(*this);
    
    vkEndCommandBuffer(_Handle);
}

void Kanas::Core::CommandBuffer::Submit()
{
}

void Kanas::Core::CommandBuffer::Barrier()
{
    VkMemoryBarrier MemoryBarrier;

    //vkCmdPipelineBarrier(_Handle,0,0,0,1,&MemoryBarrier,)
}

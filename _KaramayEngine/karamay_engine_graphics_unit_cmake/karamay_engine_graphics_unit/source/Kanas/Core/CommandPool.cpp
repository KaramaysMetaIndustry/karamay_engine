#include "CommandPool.h"
#include "CommandBuffer.h"
#include "Device.h"

Kanas::Core::CommandPool::CommandPool(Device& InDevice) :
    DeviceObject(InDevice)
{
}

Kanas::Core::CommandPool::~CommandPool()
{
    if (IsValid())
    {
        vkDestroyCommandPool(GetDevice().GetHandle(), GetHandle(), nullptr);

        ResetHandle();
    }
}

bool Kanas::Core::CommandPool::Allocate(uint32 InQueueFamilyIndex)
{
    VkCommandPoolCreateInfo CommandPoolCreateInfo;
    CommandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    CommandPoolCreateInfo.pNext = nullptr;
    CommandPoolCreateInfo.flags = {};
    CommandPoolCreateInfo.queueFamilyIndex = InQueueFamilyIndex;

    VkResult Result = vkCreateCommandPool(GetDevice().GetHandle(), &CommandPoolCreateInfo, nullptr, &_Handle);

    if (Result == VkResult::VK_SUCCESS)
    {
        return true;
    }

    return false;
}

VkResult Kanas::Core::CommandPool::Reset(VkCommandPoolResetFlags InCommandPoolResetFlags)
{
    return vkResetCommandPool(GetDevice().GetHandle(), GetHandle(), InCommandPoolResetFlags);
}

Kanas::Core::CommandBuffer* Kanas::Core::CommandPool::CreateCmdBuffer(VkCommandBufferLevel InCmdBufferLevel)
{
    const auto NewCmdBuffer = std::make_unique<CommandBuffer>(GetDevice(), *this);

    if (NewCmdBuffer && NewCmdBuffer->Allocate(InCmdBufferLevel))
    {
        CommandBuffers.push_back(NewCmdBuffer);
        return NewCmdBuffer.get();
    }

    return nullptr;
}

void Kanas::Core::CommandPool::ReleaseCmdBuffer(CommandBuffer* InCmdBufferToRelease)
{
    if (InCmdBufferToRelease)
    {
        for (const auto& CmdBuffer : CommandBuffers)
        {
            if (CmdBuffer.get() == InCmdBufferToRelease)
            {
                
            }
        }
    }
}

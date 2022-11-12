#include "CommandPool.h"
#include "CommandBuffer.h"
#include "Device.h"
#include "PhysicalDevice.h"

Kanas::Core::CommandPool::CommandPool(Device& InDevice) :
    DeviceObject(InDevice)
{
    std::vector<VkQueueFamilyProperties> QueueFamilyProperties;
    GetDevice().GetPhysicalDevice().GetQueueFamilyProperties(QueueFamilyProperties);

    QueueFamilyProperties[0].queueFlags;
    QueueFamilyProperties[0].timestampValidBits;

}

Kanas::Core::CommandPool::~CommandPool()
{
    if (IsValid())
    {
        vkDestroyCommandPool(GetDevice().GetHandle(), GetHandle(), nullptr);

        ResetHandle();
    }
}

bool Kanas::Core::CommandPool::Allocate(uint32 InQueueFamilyIndex, bool bInTransientBuffer, bool bInCanBufferResetSelf)
{
    VkCommandPoolCreateFlags CommandPoolCreateFlags = 0;

    if (bInTransientBuffer)
    {
        CommandPoolCreateFlags |= VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
    }
    
    if (!bInCanBufferResetSelf)
    {
        CommandPoolCreateFlags |= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
    }

    VkCommandPoolCreateInfo CommandPoolCreateInfo;
    CommandPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    CommandPoolCreateInfo.pNext = nullptr;
    CommandPoolCreateInfo.flags = CommandPoolCreateFlags;
    CommandPoolCreateInfo.queueFamilyIndex = InQueueFamilyIndex;

    VkResult Result = vkCreateCommandPool(GetDevice().GetHandle(), &CommandPoolCreateInfo, nullptr, &_Handle);

    if (Result == VkResult::VK_SUCCESS)
    {
        bCanBufferResetSelf = bInCanBufferResetSelf;
        return true;
    }

    return false;
}

bool Kanas::Core::CommandPool::CanBufferReset() const
{
    return bCanBufferResetSelf;
}

bool Kanas::Core::CommandPool::IsTransientBuffer() const
{
    return bTransientBuffer;
}

VkResult Kanas::Core::CommandPool::Reset(bool bInRecycle)
{
    VkCommandPoolResetFlags CommandPoolResetFlags = 0;
    
    if (bInRecycle)
    {
        CommandPoolResetFlags |= VkCommandPoolResetFlagBits::VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT; // release resources
    }

    return vkResetCommandPool(GetDevice().GetHandle(), GetHandle(), CommandPoolResetFlags);
}

Kanas::Core::CommandBuffer* Kanas::Core::CommandPool::CreateCmdBuffer(VkCommandBufferLevel InCmdBufferLevel)
{
    const auto NewCmdBuffer = std::make_unique<CommandBuffer>(GetDevice(), *this);

    if (NewCmdBuffer && NewCmdBuffer->Allocate(InCmdBufferLevel))
    {
        CmdBuffers.emplace_back(NewCmdBuffer);
        return NewCmdBuffer.get();
    }

    return nullptr;
}

void Kanas::Core::CommandPool::ReleaseCmdBuffer(CommandBuffer* InCmdBufferToRelease)
{
    if (InCmdBufferToRelease)
    {
        for (auto It = CmdBuffers.cbegin(); It != CmdBuffers.cend(); ++It)
        {
            if ((*It).get() == InCmdBufferToRelease)
            {
                CmdBuffers.erase(It);
                break;
            }
        }
    }
}

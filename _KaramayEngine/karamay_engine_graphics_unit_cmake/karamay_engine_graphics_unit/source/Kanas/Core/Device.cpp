#include "Device.h"
#include "PhysicalDevice.h"
#include "Queue.h"
#include "Fence.h"
#include "Semaphore.h"
#include "Event.h"
#include "CommandBuffer.h"
#include "DeviceMemory.h"
#include "Buffer.h"
#include "BufferView.h"
#include "Image.h"
#include "ImageView.h"
#include "Framebuffer.h"
#include "ShaderModule.h"
#include "Sampler.h"
#include "DescriptorPool.h"
#include "CommandPool.h"


bool Kanas::Core::FDevice::Allocate()
{
    VkDeviceCreateFlags DeviceCreateFlags;

    TVector<VkDeviceQueueCreateInfo> QueueCreateInfos;

    TVector<VkQueueFamilyProperties> PropertiesArr;
    GetPhysicalDevice().GetQueueFamilyProperties(PropertiesArr);

    for (const auto& Properties : PropertiesArr)
    {
        Properties.queueCount;
        Properties.queueFlags;
        Properties.minImageTransferGranularity;
        Properties.timestampValidBits;

        const bool bIsProtectedQueue = false;
        VkDeviceQueueCreateFlags QueueCreateFlags;
        if (bIsProtectedQueue)
        {
            QueueCreateFlags |= VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT;
        }

        VkDeviceQueueCreateInfo QueueCreateInfo{};
        QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        QueueCreateInfo.pNext = nullptr;
        QueueCreateInfo.flags = QueueCreateFlags;
        QueueCreateInfo.queueFamilyIndex;
        QueueCreateInfo.queueCount;
        QueueCreateInfo.pQueuePriorities;

        QueueCreateInfos.emplace_back(QueueCreateInfo);
    }

    TVector<const char*> EnabledLayerNames;
    TVector<const char*> EnabledExtensionNames;

    VkPhysicalDeviceFeatures Features;
    GetPhysicalDevice().GetFeatures(Features);

    VkDeviceCreateInfo DeviceCreateInfo;
    DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    DeviceCreateInfo.pNext = nullptr;
    DeviceCreateInfo.flags = DeviceCreateFlags;
    DeviceCreateInfo.queueCreateInfoCount = static_cast<uint32>(QueueCreateInfos.size());
    DeviceCreateInfo.pQueueCreateInfos = QueueCreateInfos.data();
    DeviceCreateInfo.enabledLayerCount = static_cast<uint32>(EnabledLayerNames.size());
    DeviceCreateInfo.ppEnabledLayerNames = EnabledLayerNames.data();
    DeviceCreateInfo.enabledExtensionCount = static_cast<uint32>(EnabledExtensionNames.size());
    DeviceCreateInfo.ppEnabledExtensionNames = EnabledExtensionNames.data();
    DeviceCreateInfo.pEnabledFeatures = &Features;

    const VkResult Result = vkCreateDevice(GPU.GetHandle(), &DeviceCreateInfo, nullptr, &_Handle);

    if (Result == VK_SUCCESS)
    {
        return true;
    }

    return false;
}

Kanas::Core::FDevice::FDevice(FPhysicalDevice& InPhysicalDevice) :
    GPU(InPhysicalDevice)
{
}

Kanas::Core::FDevice::~FDevice()
{

}

TSharedPtr<Kanas::Core::FQueue> Kanas::Core::FDevice::GetQueue(uint32 InQueueFamilyIndex, uint32 InQueueIndex)
{
    TSharedPtr<FQueue> NewQueue = MakeShared<FQueue>(*this);

    if (NewQueue && NewQueue->Allocate(InQueueFamilyIndex, InQueueIndex))
    {
        return NewQueue;
    }

    return nullptr;
}

TSharedPtr<Kanas::Core::FBuffer> Kanas::Core::FDevice::CreateBuffer(uint64 InSize, FBufferUsage Usage, TSharedPtr<FConcurrentGuide> ConcurrentGuide)
{
    if (const auto NewBuffer = MakeShared<FBuffer>(*this))
    {
        if (NewBuffer->Allocate(InSize, Usage, ConcurrentGuide))
        {
            return NewBuffer;
        }
    }

    return nullptr;
}

TSharedPtr<Kanas::Core::FBufferView> Kanas::Core::FDevice::CreateBufferView(TSharedPtr<FBuffer> Buffer, VkFormat Format, VkDeviceSize Offset, VkDeviceSize Range)
{
    if (const auto NewBufferView = MakeShared<FBufferView>(*this))
    {
        if (NewBufferView->Allocate(Buffer, Format, Offset, Range))
        {
            return NewBufferView;
        }
    }

    return nullptr;
}

TSharedPtr<Kanas::Core::FImage > Kanas::Core::FDevice::CreateImage()
{
    if (const auto NewImage = MakeShared<FImage>(*this))
    {
        if (NewImage->Allocate())
        {
            return NewImage;
        }
    }
    
    return nullptr;
}

TSharedPtr<Kanas::Core::FImageView> Kanas::Core::FDevice::CreateImageView(TSharedPtr<FImage> Image, VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange)
{
    if (const auto NewImageView = MakeShared<FImageView>(*this))
    {
        if (NewImageView->Allocate(Image, InViewType, InFormat, InComponents, InSubresourceRange))
        {
            return NewImageView;
        }
    }

    return nullptr;
}

TSharedPtr<Kanas::Core::FFramebuffer> Kanas::Core::FDevice::CreateFramebuffer()
{
    if (const auto NewFramebuffer = MakeShared<FFramebuffer>(*this))
    {
        if (NewFramebuffer->Allocate())
        {
            return NewFramebuffer;
        }

    }
    return nullptr;
}

Kanas::Core::FDescriptorPool* Kanas::Core::FDevice::CreateDescriptorPool()
{
    if (const auto NewDescriptorPool = MakeShared<FDescriptorPool>(*this))
    {
    }


    return nullptr;
}

TSharedPtr<Kanas::Core::FShaderModule> Kanas::Core::FDevice::CreateShaderModule(const TVector<uint32>& ShaderCode)
{
    if (const auto NewShaderModule = MakeShared<FShaderModule>(*this))
    {
        if (NewShaderModule->Allocate(ShaderCode))
        {
            return NewShaderModule;
        }
    }
    return nullptr;
}

TSharedPtr<Kanas::Core::FFence> Kanas::Core::FDevice::CreateFence(bool IsDefaultSignaled)
{
    const TSharedPtr<FFence> NewFence = MakeShared<FFence>(*this);

    if (NewFence && NewFence->Allocate(IsDefaultSignaled))
    {
        return NewFence;
    }

    return nullptr;
}

TSharedPtr<Kanas::Core::FSemaphore> Kanas::Core::FDevice::CreateSemaphore()
{
    if (const auto NewSemaphore = MakeShared<FSemaphore>(*this))
    {
        if (NewSemaphore->Allocate(VK_SEMAPHORE_TYPE_BINARY, 0))
        {
            return NewSemaphore;
        }
    }
    return nullptr;
}

TSharedPtr<Kanas::Core::FEvent> Kanas::Core::FDevice::CreateEvent()
{
    if (const auto NewEvent = MakeShared<FEvent>(*this))
    {
        if (NewEvent->Allocate())
        {
            return NewEvent;
        }
    }
    return nullptr;
}

TSharedPtr<Kanas::Core::FSampler> Kanas::Core::FDevice::CreateSampler()
{
    if (const auto NewSampler = MakeShared<FSampler>(*this))
    {
        if (NewSampler->Allocate())
        {
            return NewSampler;
        }
    }
    return nullptr;
}

void Kanas::Core::FDevice::Test()
{
    const auto TransferQueue = GetQueue(0, 0);
    const auto GraphicsQueue = GetQueue(1, 0);

    TVector<TSharedPtr<FSemaphore>> WaitSemaphores;
    TVector<VkPipelineStageFlags> WaitDstStageMasks;

    TVector<TSharedPtr<FCommandBuffer>> CmdBuffers;

    TVector<TSharedPtr<FQueue>> Queues{ TransferQueue, GraphicsQueue };

    auto ConcurrentGuide = MakeShared<FConcurrentGuide>(Queues);
    
    auto NewBuffer = CreateBuffer(1024, FBufferUsage().UniformBuffer().TransferSrc().TransferDst(), ConcurrentGuide);

}
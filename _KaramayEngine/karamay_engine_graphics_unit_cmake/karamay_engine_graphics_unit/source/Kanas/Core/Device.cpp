#include "Device.h"
#include "PhysicalDevice.h"
#include "Queue.h"
#include "Fence.h"
#include "Semaphore.h"
#include "CommandBuffer.h"
#include "DeviceMemory.h"
#include "Buffer.h"
#include "Image.h"

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

Kanas::Core::TSharedPtr<Kanas::Core::FQueue> Kanas::Core::FDevice::GetQueue(uint32 InQueueFamilyIndex, uint32 InQueueIndex)
{
    TSharedPtr<FQueue> NewQueue = MakeShared<FQueue>(*this);

    if (NewQueue && NewQueue->Allocate(InQueueFamilyIndex, InQueueIndex))
    {
        return NewQueue;
    }

    return nullptr;
}

Kanas::Core::TSharedPtr<Kanas::Core::FBuffer> Kanas::Core::FDevice::CreateBuffer(uint64 InSize, FBufferUsage Usage, TSharedPtr<FConcurrentGuide> ConcurrentGuide)
{
    TSharedPtr<FBuffer> NewBuffer = MakeShared<FBuffer>(*this);
    
    if (NewBuffer && NewBuffer->Allocate(InSize, Usage, ConcurrentGuide))
    {
        return NewBuffer;
    }

    return nullptr;
}

Kanas::Core::TSharedPtr<Kanas::Core::FFence> Kanas::Core::FDevice::CreateFence(bool IsDefaultSignaled)
{
    const TSharedPtr<FFence> NewFence = MakeShared<FFence>(*this);

    if (NewFence && NewFence->Allocate(IsDefaultSignaled))
    {
        return NewFence;
    }

    return nullptr;
}

Kanas::Core::TSharedPtr<Kanas::Core::FSemaphore> Kanas::Core::FDevice::CreateSemaphore()
{
    Semaphore* NewSemaphore = new Semaphore(*this);
    
    if (NewSemaphore && NewSemaphore->Allocate(VK_SEMAPHORE_TYPE_BINARY, 0))
    {
        return NewSemaphore;
    }
    
    return nullptr;
}

void Kanas::Core::FDevice::Test()
{
    TSharedPtr<FQueue> TransferQueue = GetQueue(0, 0);
    TSharedPtr<FQueue> GraphicsQueue = GetQueue(1, 0);

    TVector<TSharedPtr<FSemaphore>> WaitSemaphores;
    TVector<VkPipelineStageFlags> WaitDstStageMasks;

    TVector<TSharedPtr<FCommandBuffer>> CmdBuffers;

    TVector<TSharedPtr<FQueue>> Queues{ TransferQueue, GraphicsQueue };

    auto ConcurrentGuide = MakeShared<FConcurrentGuide>(Queues);
    
    auto NewBuffer = CreateBuffer(1024, FBufferUsage().UniformBuffer().TransferSrc().TransferDst(), ConcurrentGuide);

}
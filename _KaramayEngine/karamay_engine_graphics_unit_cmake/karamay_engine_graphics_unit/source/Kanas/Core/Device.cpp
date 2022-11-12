#include "Device.h"
#include "PhysicalDevice.h"
#include "Queue.h"
#include "Fence.h"
#include "Semaphore.h"
#include "CommandBuffer.h"
#include "DeviceMemory.h"

bool Kanas::Core::Device::Allocate()
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

        VkDeviceQueueCreateInfo QueueCreateInfo;
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

Kanas::Core::Device::Device(PhysicalDevice& InPhysicalDevice) :
    GPU(InPhysicalDevice)
{
}

Kanas::Core::Device::~Device()
{

}

Kanas::Core::Queue* Kanas::Core::Device::GetQueue(uint32 InQueueFamilyIndex, uint32 InQueueIndex)
{
    Queue* NewQueue = new Queue(*this);
    if (NewQueue && NewQueue->Allocate(InQueueFamilyIndex, InQueueIndex))
    {
        return NewQueue;
    }
    return nullptr;
}

Kanas::Core::DeviceMemory* Kanas::Core::Device::CreateDeviceMemory(VkDeviceSize InAllocSize, uint32 InMemTypeIndex)
{
    DeviceMemory* NewMem = new DeviceMemory(*this);
    if (NewMem && NewMem->Allocate(InAllocSize, InMemTypeIndex))
    {
        return NewMem;
    }
    return nullptr;
}

Kanas::Core::Fence* Kanas::Core::Device::CreateFence(bool IsDefaultSignaled)
{
    Fence* NewFence = new Fence(*this);

    if (NewFence && NewFence->Allocate(IsDefaultSignaled))
    {
        return NewFence;
    }

    return nullptr;
}

Kanas::Core::Semaphore* Kanas::Core::Device::CreateSemaphore()
{
    Semaphore* NewSemaphore = new Semaphore(*this);
    
    if (NewSemaphore && NewSemaphore->Allocate(VK_SEMAPHORE_TYPE_BINARY, 0))
    {
        return NewSemaphore;
    }
    
    return nullptr;
}

void Kanas::Core::Device::Test()
{
    Queue* TransferQueue = GetQueue(0, 0);
    Queue* GraphicsQueue = GetQueue(1, 0);

    CommandBuffer* CmdBuffer = nullptr;

    std::vector<Semaphore*> WaitSemaphores;
    std::vector<VkPipelineStageFlags> WaitDstStageMasks;

    std::vector<Semaphore*> SignalSemaphores;
    std::vector<CommandBuffer*> CmdBuffers;

    Fence* NewFence = CreateFence();
    Semaphore* NewSemaphore = CreateSemaphore();

    VkSemaphoreSignalInfo SemaphoreSignalInfo;
    VkBindSparseInfo BindSpareInfo;

}
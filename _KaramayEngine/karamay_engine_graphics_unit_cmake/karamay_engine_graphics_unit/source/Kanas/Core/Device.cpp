#include "Device.h"
#include "Queue.h"
#include "Fence.h"
#include "Semaphore.h"
#include "CommandBuffer.h"
#include "DeviceMemory.h"

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
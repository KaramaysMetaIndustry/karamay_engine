#include "Device.h"
#include "Queue.h"
#include "Fence.h"
#include "Semaphore.h"

Kanas::Core::Queue* Kanas::Core::Device::GetQueue(uint32 InQueueFamilyIndex, uint32 InQueueIndex)
{
    Queue* NewQueue = new Queue(*this);
    if (NewQueue && NewQueue->Allocate(InQueueFamilyIndex, InQueueIndex))
    {
        return NewQueue;
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
    
    if (NewSemaphore && NewSemaphore->Allocate())
    {
        return NewSemaphore;
    }
    
    return nullptr;
}

void Kanas::Core::Device::Test()
{
    Queue* TransferQueue = GetQueue(0, 0);
    Queue* GraphicsQueue = GetQueue(1, 0);


    std::vector<Semaphore*> WaitSemaphores;
    std::vector<VkPipelineStageFlags> WaitDstStageMasks;

    std::vector<Semaphore*> SignalSemaphores;
    std::vector<CommandBuffer*> CmdBuffers;

    VkSubmitInfo NewSubmitInfo;
    NewSubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    NewSubmitInfo.pNext = nullptr;
    NewSubmitInfo.waitSemaphoreCount;
    NewSubmitInfo.pWaitSemaphores;
    NewSubmitInfo.pWaitDstStageMask;

    NewSubmitInfo.commandBufferCount;
    NewSubmitInfo.pCommandBuffers;

    NewSubmitInfo.signalSemaphoreCount;
    NewSubmitInfo.pSignalSemaphores;

    Fence* NewFence = CreateFence();
    Semaphore* NewSemaphore = CreateSemaphore();

    VkSemaphoreSignalInfo SemaphoreSignalInfo;


    VkBindSparseInfo BindSpareInfo;

    TransferQueue->BindSpare(BindSpareInfo);
    NewFence->Reset();

    TransferQueue->Submit(NewSubmitInfo, NewFence);
    
    if (!NewFence->Wait(10))
    {
        return;
    };

    GraphicsQueue->Submit(NewSubmitInfo);

}
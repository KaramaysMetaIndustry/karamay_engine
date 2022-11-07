#include "Queue.h"
#include "Device.h"
#include "Fence.h"
#include "CommandBuffer.h"

bool Kanas::Core::Queue::Allocate(uint32 InQueueFamilyIndex, uint32 InQueueIndex)
{
	vkGetDeviceQueue(GetDevice().GetHandle(), InQueueFamilyIndex, InQueueIndex, &_Handle);
	return true;
}

Kanas::Core::Queue::Queue(Device& InDevice) :
	DeviceObject(InDevice)
{
}

Kanas::Core::Queue::~Queue()
{
}

void Kanas::Core::Queue::BindSpare(const std::vector<BindSpareInfo>& InBindSparseInfos, Fence* InFence)
{
	std::vector<VkBindSparseInfo> BindSpareInfos;

	for(const auto Info : InBindSparseInfos)
	{
		VkBindSparseInfo BindSpareInfo;
		BindSpareInfo.sType = VK_STRUCTURE_TYPE_BIND_SPARSE_INFO;
		BindSpareInfo.pNext = nullptr;

		BindSpareInfo.waitSemaphoreCount;
		BindSpareInfo.pWaitSemaphores;

		BindSpareInfo.bufferBindCount;
		BindSpareInfo.pBufferBinds;

		BindSpareInfo.imageOpaqueBindCount;
		BindSpareInfo.pImageOpaqueBinds;

		BindSpareInfo.imageBindCount;
		BindSpareInfo.pImageBinds;

		BindSpareInfo.signalSemaphoreCount;
		BindSpareInfo.pSignalSemaphores;
	}
	
	VkFence FenceHandle = InFence ? InFence->GetHandle() : VK_NULL_HANDLE;

	VkResult Result = vkQueueBindSparse(GetHandle(), static_cast<uint32>(BindSpareInfos.size()), BindSpareInfos.data(), FenceHandle);
}

void Kanas::Core::Queue::WaitIdle()
{
	VkResult Result = vkQueueWaitIdle(GetHandle());
}

void Kanas::Core::Queue::Submit(const std::vector<SubmissionBatch>& InBatches, Fence* InFence)
{
	std::vector<VkSubmitInfo> SubmitInfos;
	SubmitInfos.reserve(InBatches.size());

	for (const auto& Batch : InBatches)
	{
		std::vector<VkSemaphore> WaitSemaphoreHandles;
		std::vector<VkPipelineStageFlags> PipelineStageFlagsArr;

		std::vector<VkCommandBuffer> CmdBufferHandles;

		std::vector<VkSemaphore> SignalSemaphoreHandles;

		VkSubmitInfo SubmitInfo;
		SubmitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		SubmitInfo.pNext = nullptr;
		// Block the device until these semaphores signaled at the WaitDstStage
		// 在哪些阶段需要确认哪些信号量被激活，Command才能继续
		SubmitInfo.waitSemaphoreCount = static_cast<uint32>(WaitSemaphoreHandles.size());
		SubmitInfo.pWaitSemaphores = WaitSemaphoreHandles.data();
		SubmitInfo.pWaitDstStageMask = PipelineStageFlagsArr.data();
		// 需要提交执行的Buffers
		// 按順序開始執行，并行執行，不保證按順序結束
		SubmitInfo.commandBufferCount = static_cast<uint32>(CmdBufferHandles.size());
		SubmitInfo.pCommandBuffers = CmdBufferHandles.data();
		// 当Batch Execution 结束的时候激活的信号量
		SubmitInfo.signalSemaphoreCount = static_cast<uint32>(SignalSemaphoreHandles.size());
		SubmitInfo.pSignalSemaphores = SignalSemaphoreHandles.data();

		SubmitInfos.emplace_back(SubmitInfo);
	}

	VkFence FenceHandle = InFence ? FenceHandle = InFence->GetHandle() : VK_NULL_HANDLE;

	VkResult Result = vkQueueSubmit(GetHandle(), static_cast<uint32>(SubmitInfos.size()), SubmitInfos.data(), FenceHandle);
}

void Kanas::Core::Queue::PresetKHR(const VkPresentInfoKHR& InPresentInfo)
{
	VkResult Result = vkQueuePresentKHR(GetHandle(), &InPresentInfo);
}

Kanas::Core::QueuePool* Kanas::Core::Queue::GetOwner() const
{
	return Owner;
}
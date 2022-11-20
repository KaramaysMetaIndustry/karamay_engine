#include "queue.h"
#include "device.h"
#include "fence.h"
#include "command_buffer.h"

bool kanas::core::queue::alllocate(std::uint32_t InQueueFamilyIndex, std::uint32_t InQueueIndex)
{
	vkGetDeviceQueue(get_device().get_handle(), InQueueFamilyIndex, InQueueIndex, &handle);
	return true;
}

kanas::core::queue::queue(device& owner) :
	device_object(owner)
{
}

kanas::core::queue::~queue()
{
}

void kanas::core::queue::BindSpare(const std::vector<BindSpareInfo>& InBindSparseInfos, fence* InFence)
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
	
	VkFence FenceHandle = InFence ? InFence->get_handle() : VK_NULLhandle;

	VkResult Result = vkQueueBindSparse(get_handle(), static_cast<std::uint32_t>(BindSpareInfos.size()), BindSpareInfos.data(), FenceHandle);
}

void kanas::core::queue::WaitIdle()
{
	VkResult Result = vkQueueWaitIdle(get_handle());
}

void kanas::core::queue::Submit(const std::vector<SubmissionBatch>& InBatches, fence* InFence)
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
		SubmitInfo.waitSemaphoreCount = static_cast<std::uint32_t>(WaitSemaphoreHandles.size());
		SubmitInfo.pWaitSemaphores = WaitSemaphoreHandles.data();
		SubmitInfo.pWaitDstStageMask = PipelineStageFlagsArr.data();
		// 需要提交执行的Buffers
		// 按順序開始執行，并行執行，不保證按順序結束
		SubmitInfo.commandBufferCount = static_cast<std::uint32_t>(CmdBufferHandles.size());
		SubmitInfo.pCommandBuffers = CmdBufferHandles.data();
		// 当Batch Execution 结束的时候激活的信号量
		SubmitInfo.signalSemaphoreCount = static_cast<std::uint32_t>(SignalSemaphoreHandles.size());
		SubmitInfo.pSignalSemaphores = SignalSemaphoreHandles.data();

		SubmitInfos.emplace_back(SubmitInfo);
	}

	VkFence FenceHandle = InFence ? FenceHandle = InFence->get_handle() : VK_NULLhandle;

	VkResult Result = vkQueueSubmit(get_handle(), static_cast<std::uint32_t>(SubmitInfos.size()), SubmitInfos.data(), FenceHandle);
}

void kanas::core::queue::PresetKHR(const VkPresentInfoKHR& InPresentInfo)
{
	VkResult Result = vkQueuePresentKHR(get_handle(), &InPresentInfo);
}

kanas::core::queuePool* kanas::core::queue::GetOwner() const
{
	return Owner;
}
#include "Queue.h"
#include "Device.h"
#include "Fence.h"
#include "CommandBuffer.h"

bool Kanas::Core::FQueue::Allocate(uint32 InQueueFamilyIndex, uint32 InQueueIndex)
{
	vkGetDeviceQueue(GetDevice().GetHandle(), InQueueFamilyIndex, InQueueIndex, &_Handle);
	return true;
}

Kanas::Core::FQueue::FQueue(FDevice& InDevice) :
	FDeviceObject(InDevice)
{
}

Kanas::Core::FQueue::~FQueue()
{
}

void Kanas::Core::FQueue::BindSpare(const std::vector<BindSpareInfo>& InBindSparseInfos, FFence* InFence)
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

void Kanas::Core::FQueue::WaitIdle()
{
	VkResult Result = vkQueueWaitIdle(GetHandle());
}

void Kanas::Core::FQueue::Submit(const TVector<SubmissionBatch>& InBatches, FFence* InFence)
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
		// ����Щ�׶���Ҫȷ����Щ�ź��������Command���ܼ���
		SubmitInfo.waitSemaphoreCount = static_cast<uint32>(WaitSemaphoreHandles.size());
		SubmitInfo.pWaitSemaphores = WaitSemaphoreHandles.data();
		SubmitInfo.pWaitDstStageMask = PipelineStageFlagsArr.data();
		// ��Ҫ�ύִ�е�Buffers
		// ������_ʼ���У����Ј��У������C�����Y��
		SubmitInfo.commandBufferCount = static_cast<uint32>(CmdBufferHandles.size());
		SubmitInfo.pCommandBuffers = CmdBufferHandles.data();
		// ��Batch Execution ������ʱ�򼤻���ź���
		SubmitInfo.signalSemaphoreCount = static_cast<uint32>(SignalSemaphoreHandles.size());
		SubmitInfo.pSignalSemaphores = SignalSemaphoreHandles.data();

		SubmitInfos.emplace_back(SubmitInfo);
	}

	VkFence FenceHandle = InFence ? FenceHandle = InFence->GetHandle() : VK_NULL_HANDLE;

	VkResult Result = vkQueueSubmit(GetHandle(), static_cast<uint32>(SubmitInfos.size()), SubmitInfos.data(), FenceHandle);
}

void Kanas::Core::FQueue::PresetKHR(const VkPresentInfoKHR& InPresentInfo)
{
	VkResult Result = vkQueuePresentKHR(GetHandle(), &InPresentInfo);
}

Kanas::Core::FQueuePool* Kanas::Core::FQueue::GetOwner() const
{
	return Owner;
}
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FQueuePool;
class FFence;
class FCommandBuffer;

struct SubmissionBatch
{
	std::vector<std::pair<Semaphore*, VkPipelineStageFlags>> SemaphoreToWaitBeforeExecution;

	std::vector<CommandBuffer*> CmdBuffers;

	std::vector<Semaphore*> SemaphoreToSignalAfterExecution;

};

struct BindSpareInfo
{

};

class FQueue final : public FDeviceObject<VkQueue>
{
	friend class FDevice;

	bool Allocate(uint32 InQueueFamilyIndex, uint32 InQueueIndex);

public:

	FQueue(FDevice& InDevice);

	virtual ~FQueue() override;

	void BindSpare(const std::vector<BindSpareInfo>& InBindSparseInfos, FFence* InFence = nullptr);

	void WaitIdle();

	void Submit(const std::vector<SubmissionBatch>& InBatches, FFence* InFence = nullptr);

	void PresetKHR(const VkPresentInfoKHR& InPresentInfo);

	FQueuePool* GetOwner() const;

	uint32 GetFamilyIndex() const { return QueueFamilyIndex; }

private:

	FQueuePool* Owner{ nullptr };

	friend TransientQueueGroup;

	uint32 QueueFamilyIndex;

};


struct TransientQueueGroup
{

	std::vector<Queue*> Queues;

	void BindSpare();

	void Submit();

};

_KANAS_CORE_END

#endif
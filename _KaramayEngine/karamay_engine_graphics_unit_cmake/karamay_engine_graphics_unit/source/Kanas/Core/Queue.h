#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class QueuePool;
class Fence;
class CommandBuffer;

struct SubmissionBatch
{
	std::vector<std::pair<Semaphore*, VkPipelineStageFlags>> SemaphoreToWaitBeforeExecution;

	std::vector<CommandBuffer*> CmdBuffers;

	std::vector<Semaphore*> SemaphoreToSignalAfterExecution;

};

struct BindSpareInfo
{

};

class Queue final : public DeviceObject<VkQueue>
{
	friend class Device;

	bool Allocate(uint32 InQueueFamilyIndex, uint32 InQueueIndex);

public:

	Queue(Device& InDevice);

	virtual ~Queue() override;

	void BindSpare(const std::vector<BindSpareInfo>& InBindSparseInfos, Fence* InFence = nullptr);

	void WaitIdle();

	void Submit(const std::vector<SubmissionBatch>& InBatches, Fence* InFence = nullptr);

	void PresetKHR(const VkPresentInfoKHR& InPresentInfo);

	QueuePool* GetOwner() const;

private:

	QueuePool* Owner{ nullptr };

	friend TransientQueueGroup;

};


struct TransientQueueGroup
{

	std::vector<Queue*> Queues;

	void BindSpare();

	void Submit();

};

_KANAS_CORE_END

#endif
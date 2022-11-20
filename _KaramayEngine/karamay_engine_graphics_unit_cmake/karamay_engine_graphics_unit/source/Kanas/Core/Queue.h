#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class queuePool;
class fence;
class command_buffer;

struct SubmissionBatch
{
	std::vector<std::pair<semaphore*, VkPipelineStageFlags>> SemaphoreToWaitBeforeExecution;
	
	std::vector<command_buffer*> CmdBuffers;
	
	std::vector<semaphore*> SemaphoreToSignalAfterExecution;

};

struct BindSpareInfo
{

};

class queue final : public device_object<VkQueue>
{
	friend class device;

	bool alllocate(std::uint32_t InQueueFamilyIndex, std::uint32_t InQueueIndex);

public:

	queue(device& owner);

	virtual ~queue() override;

	void BindSpare(const std::vector<BindSpareInfo>& InBindSparseInfos, fence* InFence = nullptr);

	void WaitIdle();

	void Submit(const std::vector<SubmissionBatch>& InBatches, fence* InFence = nullptr);

	void PresetKHR(const VkPresentInfoKHR& InPresentInfo);

	queuePool* GetOwner() const;

	std::uint32_t GetFamilyIndex() const { return QueueFamilyIndex; }

private:

	queuePool* Owner{ nullptr };

	friend TransientQueueGroup;

	std::uint32_t QueueFamilyIndex;

};


struct TransientQueueGroup
{

	std::vector<Queue*> Queues;

	void BindSpare();

	void Submit();

};

_KANAS_CORE_END

#endif
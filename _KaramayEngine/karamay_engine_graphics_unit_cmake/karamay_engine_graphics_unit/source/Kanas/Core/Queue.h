#ifndef _QUEUE_H_
#define _QUEUE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class QueuePool;
class Fence;

class Queue final : public DeviceObject<VkQueue>
{
public:

	Queue(Device& InDevice);

	virtual ~Queue() override;

	bool Allocate(uint32 InQueueFamilyIndex, uint32 InQueueIndex);

	QueuePool* GetOwner() const;

	void BindSpare(const VkBindSparseInfo& InBindSparseInfo, Fence* InFence = nullptr);

	void WaitIdle();

	void Submit(const VkSubmitInfo& InSubmitInfo, Fence* InFence = nullptr);

	void PresetKHR(const VkPresentInfoKHR& InPresentInfo);

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
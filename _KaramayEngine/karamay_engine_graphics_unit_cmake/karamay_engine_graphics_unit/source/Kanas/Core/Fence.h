#ifndef _FENCE_H_
#define _FENCE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

/**
* Queue Submit
* Queue BindSpare
*/
class Fence final : public DeviceObject<VkFence>
{
private:

	friend class Device;
	friend class TransientFenceGroup;

	bool Allocate(bool IsSignaled);

	VkResult GetStatus();

public:

	Fence(Device& InDevice);

	virtual ~Fence() override;

	/** Block current thread until GPU has signaled this fence or timeout.
	* @param InTimeoutInNs 
	* @return TRUE if this fence is signaled, otherwise is timeout or device lost.
	*/
	bool Wait(uint64 InTimeoutInNs);

	/** Reset the fence to unsignaled state.(Non-Blocked)
	* 
	*/
	void Reset();

	/** Whether the fence is signaled.(Non-Blocked)
	* @return True if this fence is signaled, otherwise is unsignaled or device lost.
	*/
	bool IsSignaled();

};

struct TransientFenceGroup
{
	void Reset();

	bool Wait(bool InWaitAll, uint64 InTimeoutInMs);

	std::vector<Fence*> Fences;
};

_KANAS_CORE_END

#endif
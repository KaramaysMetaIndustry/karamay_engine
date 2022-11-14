#ifndef _FENCE_H_
#define _FENCE_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

/**
* Queue Submit
* Queue BindSpare
*/
class FFence final : public FDeviceObject<VkFence>
{
private:

	friend class FDevice;
	friend class FTransientFenceGroup;

	bool Allocate(bool IsSignaled);

	VkResult GetStatus();

public:

	FFence(FDevice& InDevice);

	virtual ~FFence() override;

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

struct FTransientFenceGroup
{
	void Reset();

	bool Wait(bool InWaitAll, uint64 InTimeoutInMs);

	TVector<FFence*> Fences;
};

_KANAS_CORE_END

#endif
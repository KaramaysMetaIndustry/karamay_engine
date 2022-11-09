#ifndef _DEVICE_MEMORY_H_
#define _DEVICE_MEMORY_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class DeviceMemory final : public DeviceObject<VkDeviceMemory>
{
	friend class Device;

	bool Allocate(VkDeviceSize InAllocSize, uint32 InMemTypeIndex);

public:

	DeviceMemory(Device& InDevice);

	virtual ~DeviceMemory() override;

private:

	using DeviceMemoryHandler = std::function<void(uint64 InSize, void* InData)>;

	void HandleMemory(uint64 InOffset, uint64 InSize, const DeviceMemoryHandler& InHandler, VkMemoryMapFlags InFlags);

};

_KANAS_CORE_END

#endif
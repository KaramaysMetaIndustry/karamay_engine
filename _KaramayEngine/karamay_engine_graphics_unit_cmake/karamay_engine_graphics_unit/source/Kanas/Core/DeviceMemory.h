#ifndef _DEVICE_MEMORY_H_
#define _DEVICE_MEMORY_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

struct MemoryHeapDescription
{
	bool IsDeviceLocal;
	bool IsHostVisible;
	bool IsHostCoherent;
	bool IsHostCached;
	bool IsLazilyAllocated;
	bool IsProtected;
};

struct MemoryHeap
{
	VkDeviceSize Size;

	bool IsDeviceLocal;
	bool IsMultiInstance;

	TVector<MemoryHeapDescription> Descriptions;
};

class FDeviceMemory final : public FDeviceObject<VkDeviceMemory>
{
	friend class FImage;
	friend class FBuffer;

	bool Allocate(VkDeviceSize InAllocSize, uint32 InMemTypeIndex);

public:

	FDeviceMemory(FDevice& InDevice);

	virtual ~FDeviceMemory() override;

private:

	using DeviceMemoryHandler = std::function<void(uint64 InSize, void* InData)>;

	void HandleMemory(uint64 InOffset, uint64 InSize, const DeviceMemoryHandler& InHandler, VkMemoryMapFlags InFlags);

};


class FDeviceMemoryHeap
{

};

class FDeviceMemoryStack
{

};

class FDeviceMemoryBlock
{
	uint64 Offset;
	uint32 Size;
	TSharedPtr<FDeviceMemoryHeap> Heap;
};


_KANAS_CORE_END

#endif
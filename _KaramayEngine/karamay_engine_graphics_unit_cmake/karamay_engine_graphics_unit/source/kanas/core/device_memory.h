#ifndef _DEVICE_MEMORY_H_
#define _DEVICE_MEMORY_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

struct MemoryHeapDescription
{
	bool IsDeviceLocal;
	bool IsHostVisible;
	bool IsHostCoherent;
	bool IsHostCached;
	bool IsLazilyalllocated;
	bool IsProtected;
};

struct MemoryHeap
{
	VkDeviceSize Size;

	bool IsDeviceLocal;
	bool IsMultiInstance;

	std::vector<MemoryHeapDescription> Descriptions;
};

class device_memory final : public device_object<Vkdevice_memory>
{
	friend class image;
	friend class buffer;

	bool alllocate(VkDeviceSize InAllocSize, std::uint32_t InMemTypeIndex);

public:

	device_memory(device& owner);

	virtual ~device_memory() override;

private:

	using device_memoryHandler = std::function<void(std::uint64_t InSize, void* InData)>;

	void HandleMemory(std::uint64_t InOffset, std::uint64_t InSize, const device_memoryHandler& InHandler, VkMemoryMapFlags InFlags);

};


class device_memoryHeap
{

};

class device_memoryStack
{

};

class device_memoryBlock
{
	std::uint64_t Offset;
	std::uint32_t Size;
	std::shared_ptr<device_memoryHeap> Heap;
};


_KANAS_CORE_END

#endif
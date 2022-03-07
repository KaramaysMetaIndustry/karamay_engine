#ifndef DEVICE_MEMORY_H
#define DEVICE_MEMORY_H
#include "device_object.h"

class device_memory final : public device_object<VkDeviceMemory>
{
public:

	device_memory(device& dev);

	device_memory(const device_memory&) = delete;
	device_memory& operator=(const device_memory&) = delete;

	~device_memory() override;

public:

	bool allocate(const VkMemoryRequirements& requirements) noexcept;

	void deallocate() noexcept;

public:

	/*
	* cpu ~ gpu
	* this action will cost bandwidth, and this should be called in main thread
	*/
	void execute_handler(uint64 offset, uint64 size, VkMemoryMapFlags flags, const std::function<void(uint64 size, void* data)>& handler) noexcept;

private:

	uint32 _find_memory_type(uint32 typeFilter, VkMemoryPropertyFlags properties) noexcept;
	
};

#endif
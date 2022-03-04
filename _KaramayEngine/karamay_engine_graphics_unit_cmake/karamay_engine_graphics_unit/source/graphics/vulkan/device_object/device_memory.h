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

	bool allocate(uint64 size, uint32 memory_type_index);

	void deallocate();
	
};

#endif
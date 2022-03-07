#ifndef DESCRIPTOR_POOL_H
#define DESCRIPTOR_POOL_H
#include "device_object.h"

class descriptor_pool final : public device_object<VkDescriptorPool>
{
public:

	descriptor_pool(device& dev);

	descriptor_pool(const descriptor_pool&) = delete;
	descriptor_pool& operator=(const descriptor_pool&) = delete;

	~descriptor_pool();

public:

	bool allocate() noexcept;

	void deallocate() noexcept;

public:

	void reset(VkDescriptorPoolResetFlags flags) noexcept;

};


#endif
#ifndef DESCRIPTOR_POOL_H
#define DESCRIPTOR_POOL_H
#include "device_object.h"
#include "pooled_object/descriptor_set.h"

class descriptor_set_layout;

class descriptor_pool final : public device_object<VkDescriptorPool>
{
public:

	descriptor_pool(device& dev, uint32 count, uint32 max, const VkDescriptorPoolSize& pool_size);

	descriptor_pool(const descriptor_pool&) = delete;
	descriptor_pool& operator=(const descriptor_pool&) = delete;

	~descriptor_pool();

public:
	
	std::shared_ptr<descriptor_set> create_descriptor_set(const descriptor_set_layout& layout) noexcept;

	void reset(VkDescriptorPoolResetFlags flags) noexcept;
	
};


#endif
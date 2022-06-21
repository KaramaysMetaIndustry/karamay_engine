#ifndef DESCRIPTOR_POOL_H
#define DESCRIPTOR_POOL_H
#include "device_object.h"
#include "pooled_object/descriptor_set.h"

class vk_descriptor_set_layout;

class vk_descriptor_pool final : public device_object<VkDescriptorPool>
{
public:

	vk_descriptor_pool(vk_device& dev);

	vk_descriptor_pool(const vk_descriptor_pool&) = delete;
	vk_descriptor_pool& operator=(const vk_descriptor_pool&) = delete;

	~vk_descriptor_pool();

	bool allocate(uint32 count, uint32 max, const VkDescriptorPoolSize& pool_size);

public:
	
	std::shared_ptr<vk_descriptor_set> create_descriptor_set(const vk_descriptor_set_layout& layout) noexcept;

	void reset(VkDescriptorPoolResetFlags flags) noexcept;
	
};


#endif
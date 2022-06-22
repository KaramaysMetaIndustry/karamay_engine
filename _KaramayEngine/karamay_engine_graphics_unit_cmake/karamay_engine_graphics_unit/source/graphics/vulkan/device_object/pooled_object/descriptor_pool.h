#ifndef DESCRIPTOR_POOL_H
#define DESCRIPTOR_POOL_H
#include "../device_object.h"
#include "descriptor_set.h"

class vk_descriptor_set_layout;

class vk_descriptor_pool final : public device_object<VkDescriptorPool>
{
	std::vector<std::shared_ptr<vk_descriptor_set>> _descriptor_sets;

	void _deallocate() noexcept;

public:

	vk_descriptor_pool(vk_device& dev) :
		device_object(dev)
	{}

	vk_descriptor_pool(const vk_descriptor_pool&) = delete;
	vk_descriptor_pool& operator=(const vk_descriptor_pool&) = delete;

	~vk_descriptor_pool() override
	{
		_deallocate();
	}

	bool allocate(const vk_descriptor_pool_parameters& parameters);

	void reset(VkDescriptorPoolResetFlags flags) noexcept;

	std::shared_ptr<vk_descriptor_set> create_descriptor_set(const vk_descriptor_set_layout& layout) noexcept;
	
};

#endif
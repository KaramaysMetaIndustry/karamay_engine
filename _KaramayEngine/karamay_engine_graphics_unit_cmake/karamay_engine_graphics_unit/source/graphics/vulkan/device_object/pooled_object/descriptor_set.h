#ifndef DESCRIPTOR_SET_H
#define DESCRIPTOR_SET_H
#include "../device_object.h"

class vk_descriptor_set_layout;
class vk_descriptor_pool;

class vk_descriptor_set final : public device_object<VkDescriptorSet>
{
	vk_descriptor_pool& _pool;

	void _deallocate() noexcept;

public:

	vk_descriptor_set(vk_device& dev, vk_descriptor_pool& pool) :
		device_object(dev), _pool(pool)
	{}

	~vk_descriptor_set() override
	{
		_deallocate();
	}

	bool allocate(const vk_descriptor_set_layout& set_layout);

};

#endif
#ifndef DESCRIPTOR_SET_H
#define DESCRIPTOR_SET_H
#include "../device_object.h"

class vk_descriptor_set_layout;
class vk_descriptor_pool;

class vk_descriptor_set final : public device_object<VkDescriptorSet>
{
public:

	vk_descriptor_set(vk_device& dev, vk_descriptor_set& pool);

	~vk_descriptor_set() override;

	bool allocate(const vk_descriptor_set_layout& set_layout);

private:

	vk_descriptor_pool& _pool;

};

#endif
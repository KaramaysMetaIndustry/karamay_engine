#ifndef DESCRIPTOR_SET_H
#define DESCRIPTOR_SET_H
#include "../device_object.h"

class descriptor_set_layout;
class descriptor_pool;

class descriptor_set final : public device_object<VkDescriptorSet>
{
public:

	descriptor_set(device& dev, descriptor_pool& pool, const descriptor_set_layout& set_layout);

	~descriptor_set() override;

private:

	descriptor_pool& _pool;

};

#endif
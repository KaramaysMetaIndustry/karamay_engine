#ifndef DESCRIPTOR_SET_H
#define DESCRIPTOR_SET_H
#include "../device_object.h"

class descriptor_set_layout;
class descriptor_pool;

class descriptor_set final : public device_object<VkDescriptorSet>
{

private:

	descriptor_pool& _pool;

public:

	descriptor_set(device& dev, descriptor_pool& pool);

	~descriptor_set() override;

public:

	bool allocate(descriptor_set_layout* set_layout);

	void deallocate();

};

#endif
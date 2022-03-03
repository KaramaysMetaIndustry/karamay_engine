#ifndef DESCRIPTOR_SET_H
#define DESCRIPTOR_SET_H
#include "device_object.h"

class descriptor_set final : public device_object<VkDescriptorSet>
{
public:

	bool allocate();

	void dealloate();

};

#endif
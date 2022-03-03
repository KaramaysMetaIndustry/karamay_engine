#ifndef COMMAND_POOL_H
#define COMMAND_POOL_H
#include "device_object.h"

class command_buffer;

class command_pool final : public device_object<VkCommandPool>
{
public:

	command_pool(device* dev) : device_object(dev) {}

	bool allocate(uint32 queue_family_index);

	void deallocate();

public:

	std::shared_ptr<command_buffer> create_buffer();

};

#endif
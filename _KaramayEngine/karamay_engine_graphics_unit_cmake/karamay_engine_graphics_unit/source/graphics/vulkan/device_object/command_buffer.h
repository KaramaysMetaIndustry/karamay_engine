#ifndef COMMAND_BUFFER_H
#define COMMAND_BUFFER_H
#include "device_object.h"

class command_pool;

class command_buffer final : public device_object<VkCommandBuffer>
{
private:

	command_pool& _pool;

public:

	command_buffer(device& dev, command_pool& pool);

	bool allocate(VkCommandBufferLevel level);

	void deallocate();

};


#endif
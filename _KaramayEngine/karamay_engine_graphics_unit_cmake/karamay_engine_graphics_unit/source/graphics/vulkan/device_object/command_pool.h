#ifndef COMMAND_POOL_H
#define COMMAND_POOL_H
#include "device_object.h"

class command_buffer;

class command_pool final : public device_object<VkCommandPool>
{
public:

	command_pool(device& dev, uint32 queue_family_index);

	command_pool(const command_pool&) = delete;
	command_pool& operator=(const command_pool&) = delete;

	~command_pool() override;

public:
	
	std::shared_ptr<command_buffer> create_command_buffer();

	void reset(VkCommandPoolResetFlags flags) noexcept;

};

#endif
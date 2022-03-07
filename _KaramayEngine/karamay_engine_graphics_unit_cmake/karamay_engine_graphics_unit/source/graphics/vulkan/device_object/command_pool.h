#ifndef COMMAND_POOL_H
#define COMMAND_POOL_H
#include "device_object.h"

class command_buffer;

class command_pool final : public device_object<VkCommandPool>
{
public:

	command_pool(device& dev);

	command_pool(const command_pool&) = delete;
	command_pool& operator=(const command_pool&) = delete;

	~command_pool() override;

public:

	bool allocate(uint32 queue_family_index)  noexcept;

	void deallocate()  noexcept;

public:

	void reset(VkCommandPoolResetFlags flags) noexcept;
	
public:

	std::shared_ptr<command_buffer> create_command_buffer();

};

#endif
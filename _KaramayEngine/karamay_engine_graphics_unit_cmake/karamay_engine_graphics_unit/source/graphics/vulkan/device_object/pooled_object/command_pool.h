#ifndef COMMAND_POOL_H
#define COMMAND_POOL_H
#include "../device_object.h"

class vk_command_buffer;

class vk_command_pool final : public device_object<VkCommandPool>
{

	void _deallocate() noexcept;

public:

	vk_command_pool(vk_device& dev) :
		device_object(dev)
	{}

	vk_command_pool(const vk_command_pool&) = delete;
	vk_command_pool& operator=(const vk_command_pool&) = delete;

	~vk_command_pool() override
	{
		_deallocate();
	}

	bool allocate(const vk_command_pool_parameters& parameters) noexcept;

public:
	
	std::shared_ptr<vk_command_buffer> create_command_buffer(VkCommandBufferLevel level);

	void reset(VkCommandPoolResetFlags flags) noexcept;

};

#endif
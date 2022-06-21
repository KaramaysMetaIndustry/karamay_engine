#ifndef COMMAND_POOL_H
#define COMMAND_POOL_H
#include "device_object.h"

class vk_command_buffer;

class vk_command_pool final : public device_object<VkCommandPool>
{
public:

	vk_command_pool(vk_device& dev);

	vk_command_pool(const vk_command_pool&) = delete;
	vk_command_pool& operator=(const vk_command_pool&) = delete;

	~vk_command_pool() override;

	bool allocate(uint32 queue_family_index);

public:
	
	std::shared_ptr<vk_command_buffer> create_command_buffer(VkCommandBufferLevel level);

	void reset(VkCommandPoolResetFlags flags) noexcept;

};

#endif
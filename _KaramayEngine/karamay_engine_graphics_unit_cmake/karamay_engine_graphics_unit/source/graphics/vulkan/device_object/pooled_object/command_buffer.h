#ifndef COMMAND_BUFFER_H
#define COMMAND_BUFFER_H
#include "graphics/vulkan/device_object/device_object.h"

class vk_command_pool;

class vk_command_buffer final : public device_object<VkCommandBuffer>
{
private:

	vk_command_pool& _pool;

public:

	vk_command_buffer(vk_device& dev, vk_command_pool& pool);

	vk_command_buffer(const vk_command_buffer&) = delete;
	vk_command_buffer& operator=(const vk_command_buffer&) = delete;

	~vk_command_buffer();

public:

	bool allocate(VkCommandBufferLevel level) noexcept;

	void deallocate() noexcept;

public:

	void reset(VkCommandBufferResetFlags flags) noexcept;

	void begin() noexcept
	{
		VkCommandBufferInheritanceInfo _inheritance_info{};
		_inheritance_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;

		VkCommandBufferBeginInfo _begin_info{};
		_begin_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		_begin_info.pInheritanceInfo = &_inheritance_info;
		vkBeginCommandBuffer(_handle, &_begin_info);
	}

	void end() noexcept
	{
		vkEndCommandBuffer(_handle);
	}

};


#endif
#ifndef COMMAND_BUFFER_H
#define COMMAND_BUFFER_H
#include "../device_object.h"

class command_pool;

class command_buffer final : public device_object<VkCommandBuffer>
{
private:

	command_pool& _pool;

public:

	command_buffer(device& dev, command_pool& pool);

	command_buffer(const command_buffer&) = delete;
	command_buffer& operator=(const command_buffer&) = delete;

	~command_buffer();

public:

	bool allocate(VkCommandBufferLevel level);

	void deallocate();

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
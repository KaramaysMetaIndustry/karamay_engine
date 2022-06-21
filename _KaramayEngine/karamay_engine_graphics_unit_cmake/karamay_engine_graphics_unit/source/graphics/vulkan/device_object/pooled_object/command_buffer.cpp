#include "command_buffer.h"
#include "command_pool.h"

vk_command_buffer::vk_command_buffer(vk_device& dev, vk_command_pool& pool) : device_object(dev), _pool(pool)
{
}

vk_command_buffer::~vk_command_buffer()
{
	deallocate();
}

bool vk_command_buffer::allocate(VkCommandBufferLevel level) noexcept
{
	deallocate();

	VkCommandBufferAllocateInfo _allocate_info;
	_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	_allocate_info.commandBufferCount = 1;
	_allocate_info.commandPool = _pool.handle();
	_allocate_info.level = level;

	if(vkAllocateCommandBuffers(_dev.handle(), &_allocate_info, &_handle) == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

void vk_command_buffer::deallocate() noexcept
{
	if (_handle)
	{
		vkFreeCommandBuffers(_dev.handle(), _pool.handle(), 1, &_handle);
		_handle = nullptr;
	}
}

void vk_command_buffer::reset(VkCommandBufferResetFlags flags) noexcept
{
	vkResetCommandBuffer(_handle, flags);
}

#include "command_buffer.h"
#include "command_pool.h"

bool command_buffer::allocate(VkCommandBufferLevel level)
{
	VkCommandBufferAllocateInfo _allocate_info;
	_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	_allocate_info.commandBufferCount = 1;
	_allocate_info.commandPool = _pool->handle();
	_allocate_info.level = level;

	auto _ret = vkAllocateCommandBuffers(_device->handle(), &_allocate_info, &_handle);
	if (_ret != VkResult::VK_SUCCESS)
	{
		return false;
	}
    return true;
}

void command_buffer::deallocate()
{
	vkFreeCommandBuffers(_device->handle(), _pool->handle(), 1, &_handle);
}

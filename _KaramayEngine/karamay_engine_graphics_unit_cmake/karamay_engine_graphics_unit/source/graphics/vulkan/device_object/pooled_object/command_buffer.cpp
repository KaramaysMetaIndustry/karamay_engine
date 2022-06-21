#include "command_buffer.h"
#include "graphics/vulkan/device_object/command_pool.h"

command_buffer::command_buffer(device& dev, command_pool& pool) : device_object(dev), _pool(pool)
{
}

command_buffer::~command_buffer()
{
	deallocate();
}

bool command_buffer::allocate(VkCommandBufferLevel level) noexcept
{
	deallocate();

	VkCommandBufferAllocateInfo _allocate_info;
	_allocate_info.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	_allocate_info.commandBufferCount = 1;
	_allocate_info.commandPool = _pool.handle();
	_allocate_info.level = level;

	auto _ret = vkAllocateCommandBuffers(_dev.handle(), &_allocate_info, &_handle);
	if (_ret != VkResult::VK_SUCCESS)
	{
		return false;
	}
    return true;
}

void command_buffer::deallocate() noexcept
{
	if (_handle)
	{
		vkFreeCommandBuffers(_dev.handle(), _pool.handle(), 1, &_handle);
		_handle = nullptr;
	}
}

void command_buffer::reset(VkCommandBufferResetFlags flags) noexcept
{
	vkResetCommandBuffer(_handle, flags);
}

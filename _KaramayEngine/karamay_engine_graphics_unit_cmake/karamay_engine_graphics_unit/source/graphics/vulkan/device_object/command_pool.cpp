#include "command_pool.h"
#include "command_buffer.h"

command_pool::command_pool(device& dev) : device_object(dev)
{
}

bool command_pool::allocate(uint32 queue_family_index)
{
    VkCommandPoolCreateInfo _create_info;
    _create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    _create_info.queueFamilyIndex = queue_family_index;
    vkCreateCommandPool(_device.handle(), &_create_info, nullptr, &_handle);
    return true;
}

void command_pool::deallocate()
{
    vkDestroyCommandPool(_device.handle(), _handle, nullptr);
    _handle = VK_NULL_HANDLE;
}

std::shared_ptr<command_buffer> command_pool::create_command_buffer()
{
    return std::make_shared<command_buffer>(_device, this);
}

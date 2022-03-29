#include "command_pool.h"
#include "pooled_object/command_buffer.h"

command_pool::command_pool(device& dev, uint32 queue_family_index) : device_object(dev)
{
    VkCommandPoolCreateInfo _create_info{};
    _create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    _create_info.queueFamilyIndex = queue_family_index;

    auto _result = vkCreateCommandPool(_dev.handle(), &_create_info, nullptr, &_handle);
}

command_pool::~command_pool()
{
    vkDestroyCommandPool(_dev.handle(), _handle, nullptr);
}

void command_pool::reset(VkCommandPoolResetFlags flags) noexcept
{
    if (!_handle) return;

    vkResetCommandPool(_dev.handle(), _handle, flags);
}

std::shared_ptr<command_buffer> command_pool::create_command_buffer()
{
    return std::make_shared<command_buffer>(_dev, *this);
}

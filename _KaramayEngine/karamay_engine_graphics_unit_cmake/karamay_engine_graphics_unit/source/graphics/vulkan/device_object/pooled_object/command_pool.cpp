#include "command_pool.h"
#include "command_pool.h"
#include "pooled_object/command_buffer.h"

vk_command_pool::vk_command_pool(vk_device& dev) : device_object(dev)
{
   
}

vk_command_pool::~vk_command_pool()
{
    vkDestroyCommandPool(_dev.handle(), _handle, nullptr);
}

bool vk_command_pool::allocate(uint32 queue_family_index)
{
    VkCommandPoolCreateInfo _create_info{};
    _create_info.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
    _create_info.queueFamilyIndex = queue_family_index;

    if (vkCreateCommandPool(_dev.handle(), &_create_info, nullptr, &_handle) == VkResult::VK_SUCCESS)
    {
        return true;
    }

    return false;
}

void vk_command_pool::reset(VkCommandPoolResetFlags flags) noexcept
{
    if (!_handle) return;

    vkResetCommandPool(_dev.handle(), _handle, flags);
}

std::shared_ptr<vk_command_buffer> vk_command_pool::create_command_buffer(VkCommandBufferLevel level)
{
    auto _obj = std::make_shared<vk_command_buffer>(_dev, *this);
    if (_obj && _obj->allocate(level))
    {
        return _obj;
    }
    return nullptr;
}

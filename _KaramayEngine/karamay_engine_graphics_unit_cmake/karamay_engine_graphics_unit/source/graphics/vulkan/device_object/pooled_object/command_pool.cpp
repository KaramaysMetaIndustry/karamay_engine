#include "command_pool.h"
#include "command_pool.h"
#include "command_pool.h"
#include "command_pool.h"
#include "pooled_object/command_buffer.h"

void vk_command_pool::_deallocate() noexcept
{
    if (_handle)
    {
        vkDestroyCommandPool(_dev.handle(), _handle, nullptr);
        _handle = nullptr;
    }
}

bool vk_command_pool::allocate(const vk_command_pool_parameters& parameters) noexcept
{
    if (vkCreateCommandPool(_dev.handle(), &(parameters.core()), nullptr, &_handle) == VkResult::VK_SUCCESS)
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

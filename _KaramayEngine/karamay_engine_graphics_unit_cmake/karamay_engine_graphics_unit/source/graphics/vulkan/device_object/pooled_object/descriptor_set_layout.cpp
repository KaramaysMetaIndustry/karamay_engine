#include "descriptor_set_layout.h"
#include "descriptor_set_layout.h"

void vk_descriptor_set_layout::_deallocate() noexcept
{
    if (_handle)
    {
        vkDestroyDescriptorSetLayout(_dev.handle(), _handle, nullptr);
        _handle = nullptr;
    }
}

bool vk_descriptor_set_layout::allocate(const vk_descriptor_set_layout_parameters& parameters) noexcept
{
    _deallocate();

    if (vkCreateDescriptorSetLayout(_dev.handle(), &(parameters.core()), nullptr, &_handle) = VkResult::VK_SUCCESS)
    {
        return true;
    }
    return false;
}

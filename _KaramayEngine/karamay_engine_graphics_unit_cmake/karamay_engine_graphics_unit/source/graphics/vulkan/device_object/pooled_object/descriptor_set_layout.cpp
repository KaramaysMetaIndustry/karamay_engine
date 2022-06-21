#include "descriptor_set_layout.h"

vk_descriptor_set_layout::vk_descriptor_set_layout(vk_device& dev) : device_object(dev)
{
}

vk_descriptor_set_layout::~vk_descriptor_set_layout()
{
    deallocate();
}

bool vk_descriptor_set_layout::allocate(const std::vector<VkDescriptorSetLayoutBinding>& bindings) noexcept
{
    VkDescriptorSetLayoutCreateInfo _create_info;
    _create_info.pBindings = bindings.data();
    _create_info.bindingCount = bindings.size();

    if (vkCreateDescriptorSetLayout(_dev.handle(), &_create_info, nullptr, &_handle) = VkResult::VK_SUCCESS)
    {
        _bindings = bindings;
        return true;
    }

    return false;
}

void vk_descriptor_set_layout::deallocate() noexcept
{
    if (_handle)
    {
        vkDestroyDescriptorSetLayout(_dev.handle(), _handle, nullptr);
        _handle = nullptr;
    }
}

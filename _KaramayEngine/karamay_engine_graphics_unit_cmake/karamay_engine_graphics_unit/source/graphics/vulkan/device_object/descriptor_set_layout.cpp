#include "descriptor_set_layout.h"

descriptor_set_layout::descriptor_set_layout(device& dev) : device_object(dev)
{
}

descriptor_set_layout::~descriptor_set_layout()
{
    deallocate();
}

bool descriptor_set_layout::allocate(const std::vector<VkDescriptorSetLayoutBinding>& bindings) noexcept
{
    VkDescriptorSetLayoutCreateInfo _create_info;
    _create_info.pBindings = bindings.data();
    _create_info.bindingCount = bindings.size();
    auto _ret = vkCreateDescriptorSetLayout(_dev.handle(), &_create_info, nullptr, &_handle);
    if (_ret != VkResult::VK_SUCCESS)
    {
        return false;
    }
    _bindings = bindings;
    return true;
}

void descriptor_set_layout::deallocate() noexcept
{
    if (_handle)
    {
        vkDestroyDescriptorSetLayout(_dev.handle(), _handle, nullptr);
        _handle = nullptr;
    }
}

#include "descriptor_set.h"
#include "descriptor_set_layout.h"
#include "descriptor_pool.h"

void vk_descriptor_set::_deallocate() noexcept
{
    if (_handle)
    {
        vkFreeDescriptorSets(_dev.handle(), _pool.handle(), 1, &_handle);
        _handle = nullptr;
    }
}

bool vk_descriptor_set::allocate(const vk_descriptor_set_layout& set_layout)
{
    VkDescriptorSetAllocateInfo _alloc_info;
    _alloc_info.sType;
    _alloc_info.descriptorPool = _pool.handle();
    _alloc_info.descriptorSetCount = 1;
    _alloc_info.pSetLayouts = &(set_layout.handle());

    if (vkAllocateDescriptorSets(_dev.handle(), &_alloc_info, &_handle) == VkResult::VK_SUCCESS)
    {
        return true;
    }
    return false;
}

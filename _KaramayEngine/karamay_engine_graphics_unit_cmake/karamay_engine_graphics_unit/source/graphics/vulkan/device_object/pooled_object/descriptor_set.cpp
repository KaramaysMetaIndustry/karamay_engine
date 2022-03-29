#include "descriptor_set.h"
#include "../descriptor_set_layout.h"
#include "../descriptor_pool.h"

descriptor_set::descriptor_set(device& dev, descriptor_pool& pool, const descriptor_set_layout& set_layout)
    : device_object(dev), _pool(pool)
{
    VkDescriptorSetAllocateInfo _allocate_info;
    _allocate_info.sType;
    _allocate_info.descriptorPool;
    _allocate_info.descriptorSetCount;
    _allocate_info.pSetLayouts;

    vkAllocateDescriptorSets(_dev.handle(), &_allocate_info, &_handle);
}

descriptor_set::~descriptor_set()
{
    vkFreeDescriptorSets(_dev.handle(), _pool.handle(), 1, &_handle);
}

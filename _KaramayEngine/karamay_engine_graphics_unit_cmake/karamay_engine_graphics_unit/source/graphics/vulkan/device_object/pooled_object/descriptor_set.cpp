#include "descriptor_set.h"
#include "../descriptor_set_layout.h"
#include "../descriptor_pool.h"

descriptor_set::descriptor_set(device& dev, descriptor_pool& pool) : device_object(dev), _pool(pool)
{
}

descriptor_set::~descriptor_set()
{
    deallocate();
}

bool descriptor_set::allocate(descriptor_set_layout* set_layout)
{
    VkDescriptorSetAllocateInfo _allocate_info;
    _allocate_info.sType;
    _allocate_info.descriptorPool;
    _allocate_info.descriptorSetCount;
    _allocate_info.pSetLayouts;

    vkAllocateDescriptorSets(_device.handle(), &_allocate_info, &_handle);

    return true;
}

void descriptor_set::deallocate()
{
    vkFreeDescriptorSets(_device.handle(), _pool.handle(), 1, &_handle);
    _handle = nullptr;
}

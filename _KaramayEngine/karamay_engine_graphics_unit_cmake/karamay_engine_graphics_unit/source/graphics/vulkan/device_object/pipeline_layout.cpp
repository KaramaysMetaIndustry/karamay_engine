#include "pipeline_layout.h"

pipeline_layout::pipeline_layout(device& dev) : device_object(dev)
{
}

pipeline_layout::~pipeline_layout()
{
    deallocate();
}

bool pipeline_layout::allocate()
{
    VkPipelineLayoutCreateInfo _create_info;

    auto _ret = vkCreatePipelineLayout(_device.handle(), &_create_info, nullptr, &_handle);
    if (_ret == VkResult::VK_SUCCESS)
    {
        return false;
    }
    return false;
}

void pipeline_layout::deallocate()
{
    vkDestroyPipelineLayout(_device.handle(), _handle, nullptr);
}

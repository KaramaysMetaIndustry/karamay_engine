#include "pipeline_layout.h"

pipeline_layout::pipeline_layout(device& dev) : device_object(dev)
{
}

pipeline_layout::~pipeline_layout()
{
    deallocate();
}

bool pipeline_layout::allocate(const std::vector<VkDescriptorSetLayout>& layouts, const std::vector<VkPushConstantRange>& ranges)
{
    VkPipelineLayoutCreateInfo _create_info;
    _create_info.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    _create_info.flags;
    _create_info.pSetLayouts = layouts.data();
    _create_info.setLayoutCount = layouts.size();
    _create_info.pPushConstantRanges = ranges.data();
    _create_info.pushConstantRangeCount = ranges.size();

    VkResult _ret = vkCreatePipelineLayout(_dev.handle(), &_create_info, nullptr, &_handle);
    if (_ret == VkResult::VK_SUCCESS)
    {
        return false;
    }
    return true;
}

void pipeline_layout::deallocate()
{
    if (_handle)
    {
        vkDestroyPipelineLayout(_dev.handle(), _handle, nullptr);
        _handle = nullptr;
    }
}

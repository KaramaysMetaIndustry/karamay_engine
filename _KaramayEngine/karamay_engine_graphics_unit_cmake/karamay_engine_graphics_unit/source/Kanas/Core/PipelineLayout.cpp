#include "PipelineLayout.h"
#include "Device.h"

Kanas::Core::PipelineLayout::PipelineLayout(Device& InDevice) :
    DeviceObject(InDevice)
{
}

Kanas::Core::PipelineLayout::~PipelineLayout()
{
    if (IsValid())
    {
        vkDestroyPipelineLayout(GetDevice().GetHandle(), GetHandle(), nullptr);
        
        ResetHandle();
    }
}

bool Kanas::Core::PipelineLayout::Allocate(const std::vector<DescriptorSetLayout>& InDescriptorSetLayouts, const std::vector<VkPushConstantRange> InPushConstantRanges)
{
    const std::vector<VkDescriptorSetLayout> DescriptorSetLayoutHandles;

    VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo;
    PipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    PipelineLayoutCreateInfo.flags;
    PipelineLayoutCreateInfo.pSetLayouts = DescriptorSetLayoutHandles.data();
    PipelineLayoutCreateInfo.setLayoutCount = DescriptorSetLayoutHandles.size();
    PipelineLayoutCreateInfo.pPushConstantRanges = InPushConstantRanges.data();
    PipelineLayoutCreateInfo.pushConstantRangeCount = InPushConstantRanges.size();

    VkResult Result = vkCreatePipelineLayout(GetDevice().GetHandle(), &PipelineLayoutCreateInfo, nullptr, &_Handle);
    if (Result == VkResult::VK_SUCCESS)
    {
        return true;
    }

    return false;
}

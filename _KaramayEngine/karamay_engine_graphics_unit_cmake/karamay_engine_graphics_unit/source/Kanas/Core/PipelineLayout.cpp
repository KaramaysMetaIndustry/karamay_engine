#include "PipelineLayout.h"
#include "Device.h"
#include "DescriptorSetLayout.h"

Kanas::Core::FPipelineLayout::FPipelineLayout(FDevice& InDevice) :
    FDeviceObject(InDevice)
{
}

Kanas::Core::FPipelineLayout::~FPipelineLayout()
{
    if (IsValid())
    {
        vkDestroyPipelineLayout(GetDevice().GetHandle(), GetHandle(), nullptr);
        
        ResetHandle();
    }
}

TSharedPtr<Kanas::Core::FDescriptorSetLayout> Kanas::Core::FPipelineLayout::GetDecriptorSetLayout(uint32 SetIndex) const
{
    if (DescriptorSetLayouts.size() > SetIndex)
    {
        return DescriptorSetLayouts[SetIndex];
    }
    return nullptr;
}

bool Kanas::Core::FPipelineLayout::Allocate(const TVector<TSharedPtr<FDescriptorSetLayout>>& InDescriptorSetLayouts, const TVector<VkPushConstantRange> InPushConstantRanges)
{

      // layout(push_constant) uniform BlockName {
      //  int member1;
      //  float member2;
      // } InstanceName;

    const std::vector<VkDescriptorSetLayout> DescriptorSetLayoutHandles;

    VkPipelineLayoutCreateInfo PipelineLayoutCreateInfo{};
    PipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
    PipelineLayoutCreateInfo.flags = {};
    PipelineLayoutCreateInfo.pSetLayouts = DescriptorSetLayoutHandles.data();
    PipelineLayoutCreateInfo.setLayoutCount = DescriptorSetLayoutHandles.size();
    PipelineLayoutCreateInfo.pPushConstantRanges = InPushConstantRanges.data();
    PipelineLayoutCreateInfo.pushConstantRangeCount = InPushConstantRanges.size();

    

    const VkResult PipelineCreationResult = vkCreatePipelineLayout(GetDevice().GetHandle(), &PipelineLayoutCreateInfo, nullptr, &_Handle);
    
    if (PipelineCreationResult == VK_SUCCESS)
    {
        return true;
    }

    return false;
}

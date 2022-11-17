#include "Pipeline.h"
#include "Device.h"
#include "PipelineCache.h"
#include "CommandBuffer.h"
#include "DescriptorSet.h"
#include "DescriptorSetLayout.h"
#include "PipelineLayout.h"

Kanas::Core::FPipeline::FPipeline(FDevice& InDevice, VkPipelineBindPoint InBindPoint) :
    FDeviceObject(InDevice),
    BindPoint(InBindPoint)
{
}

Kanas::Core::FPipeline::~FPipeline()
{
    if (IsValid())
    {
        vkDestroyPipeline(GetDevice().GetHandle(), GetHandle(), nullptr);
        
        ResetHandle();
    }
}

void Kanas::Core::FPipeline::CmdBind(FCommandBuffer& InRecorder)
{
    vkCmdBindPipeline(InRecorder.GetHandle(), BindPoint, GetHandle());
}

void Kanas::Core::FPipeline::CmdPushConstants(FCommandBuffer& InRecorder)
{
    if (Constants)
    {
        vkCmdPushConstants(InRecorder.GetHandle(), GetLayout()->GetHandle(), 0, 0, Constants->GetSize(), Constants->GetData());
    }
}

void Kanas::Core::FPipeline::CmdBindDescriptorSets(FCommandBuffer& InRecorder)
{
    if (!Layout)
    {
        return;
    }
    
    TVector<VkDescriptorSet> DescriptorSetHandles;
    CollectDeviceObjectHandles(Layout->GetDescriptorSetLayouts(), DescriptorSetHandles);

    vkCmdBindDescriptorSets(InRecorder.GetHandle(), BindPoint, Layout->GetHandle(), 
        0, DescriptorSetHandles.size(), DescriptorSetHandles.data(), 
        0, nullptr
    );
}

TSharedPtr<Kanas::Core::FPipelineLayout> Kanas::Core::FPipeline::GetLayout() const
{
    return Layout;
}

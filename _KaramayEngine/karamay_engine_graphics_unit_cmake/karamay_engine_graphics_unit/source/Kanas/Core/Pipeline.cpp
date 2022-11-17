#include "Pipeline.h"
#include "Device.h"
#include "PipelineCache.h"
#include "CommandBuffer.h"
#include "DescriptorSet.h"
#include "PipelineLayout.h"

Kanas::Core::FPipeline::FPipeline(FDevice& InDevice) :
    FDeviceObject(InDevice)
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
}

void Kanas::Core::FPipeline::CmdPushConstants(FCommandBuffer& InRecorder, TVector<uint8>& InValues)
{
    vkCmdPushConstants(InRecorder.GetHandle(), GetLayout()->GetHandle(), 0, 0, 1024, InValues.data());
}

void Kanas::Core::FPipeline::CmdBindDescriptorSets(FCommandBuffer& InRecorder)
{
    TVector<VkDescriptorSet> DescriptorSetHandles;
    DescriptorSetHandles.reserve(DescriptorSets.size());

	for(const auto& DescriptorSet : DescriptorSets)
    {
        DescriptorSetHandles.emplace_back(DescriptorSet->GetHandle());
    }

    vkCmdBindDescriptorSets(InRecorder.GetHandle(), GetBindPoint(), GetLayout()->GetHandle(), 0, DescriptorSetHandles.size(), DescriptorSetHandles.data(), 0, nullptr);
}

#include "Pipeline.h"
#include "Device.h"
#include "PipelineCache.h"
#include "CommandBuffer.h"
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

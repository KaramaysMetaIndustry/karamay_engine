#include "Pipeline.h"
#include "Device.h"
#include "PipelineCache.h"

Kanas::Core::Pipeline::Pipeline(Device& InDevice) :
    DeviceObject(InDevice)
{
}

Kanas::Core::Pipeline::~Pipeline()
{
    if (IsValid())
    {
        vkDestroyPipeline(GetDevice().GetHandle(), GetHandle(), nullptr);
        
        ResetHandle();
    }
}

void Kanas::Core::Pipeline::CmdBind(CommandBuffer& InRecorder)
{
}

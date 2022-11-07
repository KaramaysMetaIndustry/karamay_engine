#include "RayTracingPipeline.h"

Kanas::Core::RayTracingPipeline::RayTracingPipeline(Device& InDevice) :
	Pipeline(InDevice)
{
}

Kanas::Core::RayTracingPipeline::~RayTracingPipeline()
{
}

void Kanas::Core::RayTracingPipeline::CmdBind(CommandBuffer& InRecorder)
{
}

void Kanas::Core::RayTracingPipeline::CmdTraceRays()
{
}

void Kanas::Core::RayTracingPipeline::CmdTraceRaysIndirect()
{
}

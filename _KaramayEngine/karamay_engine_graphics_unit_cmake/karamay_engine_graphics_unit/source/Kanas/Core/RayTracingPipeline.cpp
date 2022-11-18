#include "RayTracingPipeline.h"
#include "Device.h"
#include "DeferredOperation.h"

bool Kanas::Core::FRayTracingPipeline::Allocate(TSharedPtr<FDeferredOperation> DeferredOperation)
{

	VkRayTracingShaderGroupCreateInfoKHR RayTracingShaderGroupCreateInfo{};

	RayTracingShaderGroupCreateInfo.sType = VK_STRUCTURE_TYPE_RAY_TRACING_SHADER_GROUP_CREATE_INFO_KHR;
	RayTracingShaderGroupCreateInfo.pNext = nullptr;
	RayTracingShaderGroupCreateInfo.type = VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_KHR; // TrianglesHitGroup
	RayTracingShaderGroupCreateInfo.generalShader;
	RayTracingShaderGroupCreateInfo.closestHitShader;
	RayTracingShaderGroupCreateInfo.anyHitShader;
	RayTracingShaderGroupCreateInfo.intersectionShader;
	RayTracingShaderGroupCreateInfo.pShaderGroupCaptureReplayHandle;

	VkRayTracingPipelineCreateInfoKHR RayTracingPipelineCreateInfo{};
	RayTracingPipelineCreateInfo.sType = VK_STRUCTURE_TYPE_RAY_TRACING_PIPELINE_CREATE_INFO_KHR;
	RayTracingPipelineCreateInfo.pNext = nullptr;
	RayTracingPipelineCreateInfo.flags = {};
	RayTracingPipelineCreateInfo.stageCount;
	RayTracingPipelineCreateInfo.pStages;
	RayTracingPipelineCreateInfo.groupCount;
	RayTracingPipelineCreateInfo.pGroups;
	RayTracingPipelineCreateInfo.maxPipelineRayRecursionDepth;
	RayTracingPipelineCreateInfo.pLibraryInfo;
	RayTracingPipelineCreateInfo.pLibraryInterface;
	RayTracingPipelineCreateInfo.pDynamicState;
	RayTracingPipelineCreateInfo.layout;
	RayTracingPipelineCreateInfo.basePipelineHandle;
	RayTracingPipelineCreateInfo.basePipelineIndex;

	const VkResult RayTracingPipelineCreationResult = vkCreateRayTracingPipelinesKHR(GetDevice().GetHandle(), DeferredOperation->GetHandle(), nullptr, 1, &RayTracingPipelineCreateInfo, nullptr, &_Handle);

	if (RayTracingPipelineCreationResult == VK_SUCCESS)
	{
		return true;
	}

	return false;
}

Kanas::Core::FRayTracingPipeline::FRayTracingPipeline(FDevice& InDevice) :
	FPipeline(InDevice, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR)
{
}

Kanas::Core::FRayTracingPipeline::~FRayTracingPipeline()
{
}

void Kanas::Core::FRayTracingPipeline::CmdTraceRays()
{
}

void Kanas::Core::FRayTracingPipeline::CmdTraceRaysIndirect()
{
}

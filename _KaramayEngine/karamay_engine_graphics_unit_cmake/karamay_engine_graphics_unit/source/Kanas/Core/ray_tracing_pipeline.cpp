#include "ray_tracing_pipeline.h"
#include "device.h"
#include "deferred_operation.h"

bool kanas::core::ray_tracing_piepline::alllocate(std::shared_ptr<deferred_operation> DeferredOperation)
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

	const VkResult RayTracingPipelineCreationResult = vkCreateRayTracingPipelinesKHR(get_device().get_handle(), DeferredOperation->get_handle(), nullptr, 1, &RayTracingPipelineCreateInfo, nullptr, &handle);

	if (RayTracingPipelineCreationResult == VK_SUCCESS)
	{
		return true;
	}

	return false;
}

kanas::core::ray_tracing_piepline::ray_tracing_piepline(device& owner) :
	pipeline(owner, VK_PIPELINE_BIND_POINT_RAY_TRACING_KHR)
{
}

kanas::core::ray_tracing_piepline::~ray_tracing_piepline()
{
}

void kanas::core::ray_tracing_piepline::CmdTraceRays()
{
}

void kanas::core::ray_tracing_piepline::CmdTraceRaysIndirect()
{
}

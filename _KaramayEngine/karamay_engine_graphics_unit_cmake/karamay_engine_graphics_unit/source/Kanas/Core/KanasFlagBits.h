#ifndef _KANAS_FLAG_BITS_H_
#define _KANAS_FLAG_BITS_H_

#include "Core/CoreLibrary.h"
#include "KanasCoreMacros.h"
#include "public/vulkan_core.h"

_KANAS_CORE_BEGIN

template<typename FLAF_T>
struct FVulkanFlags
{
	VkFlags GetFlags() const
	{
		return Flags;
	}

	void Reset()
	{
		Flags = 0;
	}

	void Clone(FLAF_T InFlags)
	{
		Flags = InFlags;
	}

protected:

	VkFlags Flags{ 0 };
};

#define DECAL_FLAG(FUNCTION_NAME, VK_BIT)\
auto& FUNCTION_NAME##(bool bActive = true)\
{\
	Flags |= bActive ? VK_BIT : 0;\
	return *this;\
}\
bool Is##FUNCTION_NAME##Active() const\
{\
	return Flags & VK_BIT;\
}

struct FMemoryProperty : public FVulkanFlags<FMemoryProperty>
{
	DECAL_FLAG(DeviceLocal, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT)
	DECAL_FLAG(HostVisible, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT)
	DECAL_FLAG(HostCoherent, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT)
	DECAL_FLAG(HostCached, VK_MEMORY_PROPERTY_HOST_CACHED_BIT)
	DECAL_FLAG(LazilyAllocated, VK_MEMORY_PROPERTY_LAZILY_ALLOCATED_BIT)
	DECAL_FLAG(Protected, VK_MEMORY_PROPERTY_PROTECTED_BIT)
};

struct FImageUsage : public FVulkanFlags<FImageUsage>
{
	DECAL_FLAG(TransferSrc, VK_IMAGE_USAGE_TRANSFER_SRC_BIT)
	DECAL_FLAG(TransferDst, VK_IMAGE_USAGE_TRANSFER_DST_BIT)
	DECAL_FLAG(Sampled, VK_IMAGE_USAGE_SAMPLED_BIT)
	DECAL_FLAG(Storage, VK_IMAGE_USAGE_STORAGE_BIT)
	DECAL_FLAG(ColorAttachment, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT)
	DECAL_FLAG(DepthStencilAttachment, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT)
	DECAL_FLAG(TransientAttachment, VK_IMAGE_USAGE_TRANSIENT_ATTACHMENT_BIT)
	DECAL_FLAG(InputAttachment, VK_IMAGE_USAGE_INPUT_ATTACHMENT_BIT)
};

struct FBufferUsage : public FVulkanFlags<FBufferUsage>
{
	DECAL_FLAG(TransferSrc, VK_BUFFER_USAGE_TRANSFER_SRC_BIT)
	DECAL_FLAG(TransferDst, VK_BUFFER_USAGE_TRANSFER_DST_BIT)
	DECAL_FLAG(UniformTexelBuffer, VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT)
	DECAL_FLAG(UniformTexelBuffer, VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT)
	DECAL_FLAG(StorageTexelBuffer, VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT)
	DECAL_FLAG(UniformBuffer, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT)
	DECAL_FLAG(StorageBuffer, VK_BUFFER_USAGE_STORAGE_BUFFER_BIT)
	DECAL_FLAG(IndexBuffer, VK_BUFFER_USAGE_INDEX_BUFFER_BIT)
	DECAL_FLAG(VertexBuffer, VK_BUFFER_USAGE_VERTEX_BUFFER_BIT)
	DECAL_FLAG(IndirectBuffer, VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT)
	DECAL_FLAG(ShaderDeviceAddress, VK_BUFFER_USAGE_SHADER_DEVICE_ADDRESS_BIT)
};

enum class CommandBufferLevel : uint32
{
	Primary = VK_COMMAND_BUFFER_LEVEL_PRIMARY,
	Secondary = VK_COMMAND_BUFFER_LEVEL_SECONDARY,
	MaxEnum = VK_COMMAND_BUFFER_LEVEL_MAX_ENUM
};

enum class PipelineStageFlagBits : uint8
{
	TopOfPipe = VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT,
	DrawIndirect = VK_PIPELINE_STAGE_DRAW_INDIRECT_BIT,

	VertexInput = VK_PIPELINE_STAGE_VERTEX_INPUT_BIT,

	VertexShader = VK_PIPELINE_STAGE_VERTEX_SHADER_BIT,
	TessellationControlShader = VK_PIPELINE_STAGE_TESSELLATION_CONTROL_SHADER_BIT,
	TessellationEvaluationShader = VK_PIPELINE_STAGE_TESSELLATION_EVALUATION_SHADER_BIT,
	GeometryShader = VK_PIPELINE_STAGE_GEOMETRY_SHADER_BIT,
	FragmentShader = VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT,

	EarlyFragmentTests = VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT,
	LateFragmentTests = VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT,
	ColorAttachmentOutput = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT,

	ComputeShader = VK_PIPELINE_STAGE_COMPUTE_SHADER_BIT,

	Transfer = VK_PIPELINE_STAGE_TRANSFER_BIT,

	BottomOfPipe = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT,

	Host = VK_PIPELINE_STAGE_HOST_BIT,

	AllGraphics = VK_PIPELINE_STAGE_ALL_GRAPHICS_BIT,
	AllCommands = VK_PIPELINE_STAGE_ALL_COMMANDS_BIT,

	TransformFeedbackEXT = VK_PIPELINE_STAGE_TRANSFORM_FEEDBACK_BIT_EXT,
	ConditionalRenderingEXT = VK_PIPELINE_STAGE_CONDITIONAL_RENDERING_BIT_EXT,
	AccelerationStructureBuildKHR = VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_KHR,
	RayTracingShaderKHR = VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_KHR,
	ShadingRateImage = VK_PIPELINE_STAGE_SHADING_RATE_IMAGE_BIT_NV,
	TaskShaderNV = VK_PIPELINE_STAGE_TASK_SHADER_BIT_NV,
	MeshShaderNV = VK_PIPELINE_STAGE_MESH_SHADER_BIT_NV,

	FragmentDensityProcessEXT = VK_PIPELINE_STAGE_FRAGMENT_DENSITY_PROCESS_BIT_EXT,
	CommandPrepocessNV = VK_PIPELINE_STAGE_COMMAND_PREPROCESS_BIT_NV,
	NoneKHR = VK_PIPELINE_STAGE_NONE_KHR,
	RayTracingShaderNV = VK_PIPELINE_STAGE_RAY_TRACING_SHADER_BIT_NV,
	AccelerationStructureBuildNV = VK_PIPELINE_STAGE_ACCELERATION_STRUCTURE_BUILD_BIT_NV,
	FragmentShadingRateAttachmentKHR = VK_PIPELINE_STAGE_FRAGMENT_SHADING_RATE_ATTACHMENT_BIT_KHR,
	MaxEnum = VK_PIPELINE_STAGE_FLAG_BITS_MAX_ENUM
};

_KANAS_CORE_END

#endif
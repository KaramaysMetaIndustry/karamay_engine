#ifndef _DEVICE_OBJECT_H_
#define _DEVICE_OBJECT_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class Device;

template<typename DeviceObjectT>
class DeviceRef
{

};

template<typename DeviceObjectT>
class DevicePoolRef
{

};



template<typename VkHandleT>
class DeviceObject : public VulkanObject<VkHandleT>
{

public:
	
	DeviceObject(Device& InDevice) :
		_Device(InDevice)
	{}

	virtual ~DeviceObject()
	{
	}

private:

	Device& _Device;

public:

	Device& GetDevice() { return _Device; }

	const Device& GetDevice() const { return _Device; }

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

#define VulkanEnumCast(CppEnumVal)


_KANAS_CORE_END

#endif
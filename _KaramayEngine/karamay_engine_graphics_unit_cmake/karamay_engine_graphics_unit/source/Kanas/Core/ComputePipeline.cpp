#include "ComputePipeline.h"
#include "Device.h"
#include "CommandBuffer.h"
#include "Buffer.h"
#include "PipelineLayout.h"
#include "PipelineCache.h"
#include "ShaderModule.h"

Kanas::Core::ComputePipeline::ComputePipeline(Device& InDevice) :
    Pipeline(InDevice)
{
}

Kanas::Core::ComputePipeline::~ComputePipeline()
{
}

bool Kanas::Core::ComputePipeline::Allocate(PipelineCache& InCache, PipelineLayout& InLayout, ShaderModule& InComputeShaderModule)
{
    VkPipelineShaderStageCreateInfo ShaderStageCreateInfo;
    ShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    ShaderStageCreateInfo.flags;
    ShaderStageCreateInfo.module = InComputeShaderModule.GetHandle();
    ShaderStageCreateInfo.pName = "main";
    ShaderStageCreateInfo.pSpecializationInfo = nullptr;
    ShaderStageCreateInfo.stage = VkShaderStageFlagBits::VK_SHADER_STAGE_COMPUTE_BIT;

    VkComputePipelineCreateInfo ComputePipelineCreateInfo;
    ComputePipelineCreateInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
    ComputePipelineCreateInfo.pNext = nullptr;
    ComputePipelineCreateInfo.flags;
    ComputePipelineCreateInfo.stage = ShaderStageCreateInfo;
    ComputePipelineCreateInfo.layout = InLayout.GetHandle();
    ComputePipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
    ComputePipelineCreateInfo.basePipelineIndex = -1;

    VkResult Result = vkCreateComputePipelines(GetDevice().GetHandle(), InCache.GetHandle(), 1, &ComputePipelineCreateInfo, nullptr, &_Handle);

    if (Result == VkResult::VK_SUCCESS)
    {
        return true;
    }
    return false;
}

void Kanas::Core::ComputePipeline::CmdBind(CommandBuffer& InRecorder)
{
    vkCmdBindPipeline(InRecorder.GetHandle(), VkPipelineBindPoint::VK_PIPELINE_BIND_POINT_COMPUTE, _Handle);
}

void Kanas::Core::ComputePipeline::CmdDispatch(CommandBuffer& InRecorder, const GroupCount& InGroupCount)
{
    vkCmdDispatch(InRecorder.GetHandle(), InGroupCount[0], InGroupCount[1], InGroupCount[2]);
}

void Kanas::Core::ComputePipeline::CmdDispatchBase(CommandBuffer& InRecorder, const BaseGroup& InBaseGroup, const GroupCount& InGroupCount)
{
    vkCmdDispatchBase(InRecorder.GetHandle(), InBaseGroup[0], InBaseGroup[1], InBaseGroup[2], InGroupCount[0], InGroupCount[1], InGroupCount[2]);
}

void Kanas::Core::ComputePipeline::CmdDispatchIndirect(CommandBuffer& InRecorder, Buffer& InBuffer, uint64 InOffset)
{
    vkCmdDispatchIndirect(InRecorder.GetHandle(), InBuffer.GetHandle(), InOffset);
}

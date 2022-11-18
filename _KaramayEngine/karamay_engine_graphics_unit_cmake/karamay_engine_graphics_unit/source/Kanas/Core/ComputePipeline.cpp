#include "ComputePipeline.h"
#include "Device.h"
#include "CommandBuffer.h"
#include "Buffer.h"
#include "PipelineLayout.h"
#include "PipelineCache.h"
#include "ShaderModule.h"
#include "Shader.h"

bool Kanas::Core::FComputePipeline::Allocate(TSharedPtr<FComputeShader> InComputeShader, TSharedPtr<FPipelineLayout> Layout, TSharedPtr<FPipelineCache> Cache)
{
    if (!InComputeShader)
    {
        return false;
    }
    
    if (const auto ShaderModule = InComputeShader->GetShaderModule())
    {
        VkPipelineShaderStageCreateInfo ShaderStageCreateInfo{};
        ShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
        ShaderStageCreateInfo.flags = {};
        ShaderStageCreateInfo.module = ShaderModule->GetHandle();
        ShaderStageCreateInfo.pName = InComputeShader->GetName().c_str();
        ShaderStageCreateInfo.pSpecializationInfo = nullptr;
        ShaderStageCreateInfo.stage = VK_SHADER_STAGE_COMPUTE_BIT;

        VkComputePipelineCreateInfo ComputePipelineCreateInfo{};
        ComputePipelineCreateInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
        ComputePipelineCreateInfo.pNext = nullptr;
        ComputePipelineCreateInfo.flags = {};
        ComputePipelineCreateInfo.stage = ShaderStageCreateInfo;
        ComputePipelineCreateInfo.layout = Layout->GetHandle();
        ComputePipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
        ComputePipelineCreateInfo.basePipelineIndex = -1;

        const VkResult ComputePipelineCreationResult = vkCreateComputePipelines(GetDevice().GetHandle(), Cache->GetHandle(), 1, &ComputePipelineCreateInfo, nullptr, &_Handle);

        if (ComputePipelineCreationResult == VK_SUCCESS)
        {
            return true;
        }
    }

    return false;
}

Kanas::Core::FComputePipeline::FComputePipeline(FDevice& InDevice) :
    FPipeline(InDevice, VK_PIPELINE_BIND_POINT_COMPUTE)
{
}

Kanas::Core::FComputePipeline::~FComputePipeline()
{
}

void Kanas::Core::FComputePipeline::CmdDispatch(FCommandBuffer& InRecorder, const GroupCount& InGroupCount)
{
    vkCmdDispatch(InRecorder.GetHandle(), InGroupCount[0], InGroupCount[1], InGroupCount[2]);
}

void Kanas::Core::FComputePipeline::CmdDispatchBase(FCommandBuffer& InRecorder, const BaseGroup& InBaseGroup, const GroupCount& InGroupCount)
{
    vkCmdDispatchBase(InRecorder.GetHandle(), InBaseGroup[0], InBaseGroup[1], InBaseGroup[2], InGroupCount[0], InGroupCount[1], InGroupCount[2]);
}

void Kanas::Core::FComputePipeline::CmdDispatchIndirect(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint64 InOffset)
{
    vkCmdDispatchIndirect(InRecorder.GetHandle(), InBuffer.GetHandle(), InOffset);
}

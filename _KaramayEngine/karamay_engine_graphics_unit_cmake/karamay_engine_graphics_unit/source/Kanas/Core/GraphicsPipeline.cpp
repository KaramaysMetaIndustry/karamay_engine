#include "GraphicsPipeline.h"
#include "Device.h"
#include "CommandBuffer.h"
#include "Buffer.h"
#include "PipelineCache.h"
#include "PipelineLayout.h"
#include "RenderPass.h"
#include "ShaderModule.h"

Kanas::Core::FGraphicsPipeline::FGraphicsPipeline(FDevice& InDevice) :
    FPipeline(InDevice)
{
}

Kanas::Core::FGraphicsPipeline::~FGraphicsPipeline()
{
}

bool Kanas::Core::FGraphicsPipeline::Allocate(const FGraphicsPipelineStateInitializer& InInitializer, TSharedPtr<FPipelineCache> InCache, TSharedPtr<FPipelineLayout> InLayout)
{
    TSharedPtr<FShaderModule> ShaderModule;

    VkSpecializationInfo SpecializationInfo{};
    SpecializationInfo.mapEntryCount;
    SpecializationInfo.pMapEntries;
    SpecializationInfo.dataSize;
    SpecializationInfo.pData;

    VkPipelineShaderStageCreateInfo PipelineShaderStageCreateInfo{};
    PipelineShaderStageCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
    PipelineShaderStageCreateInfo.pNext = nullptr;
    PipelineShaderStageCreateInfo.flags = {};
    PipelineShaderStageCreateInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
    PipelineShaderStageCreateInfo.module = ShaderModule->GetHandle();
    PipelineShaderStageCreateInfo.pName = "Main";
    PipelineShaderStageCreateInfo.pSpecializationInfo = &SpecializationInfo;

    TVector<VkPipelineShaderStageCreateInfo> ShaderStageCreateInfos{};
    
    TVector<VkVertexInputAttributeDescription> AttributeDescriptions;
    TVector<VkVertexInputBindingDescription> BindingDescriptions;

    VkPipelineVertexInputStateCreateInfo VertexInputStateCreateInfo{};
    VertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    VertexInputStateCreateInfo.pNext = nullptr;
    VertexInputStateCreateInfo.flags = {};
    VertexInputStateCreateInfo.pVertexAttributeDescriptions = AttributeDescriptions.data();
    VertexInputStateCreateInfo.pVertexBindingDescriptions = BindingDescriptions.data();
    VertexInputStateCreateInfo.vertexAttributeDescriptionCount = static_cast<uint32>(AttributeDescriptions.size());
    VertexInputStateCreateInfo.vertexBindingDescriptionCount = static_cast<uint32>(BindingDescriptions.size());

    VkPipelineInputAssemblyStateCreateInfo InputAssemblyStateCreateInfo{};
    InputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    InputAssemblyStateCreateInfo.pNext = nullptr;
    InputAssemblyStateCreateInfo.flags = {};
    InputAssemblyStateCreateInfo.topology = VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
    InputAssemblyStateCreateInfo.primitiveRestartEnable = false;

    VkPipelineTessellationStateCreateInfo TessellationStateCreateInfo;
    TessellationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
    TessellationStateCreateInfo.pNext = nullptr;
    TessellationStateCreateInfo.flags = {};
    TessellationStateCreateInfo.patchControlPoints = 0;

   TVector<VkViewport> Viewports;
   TVector<VkRect2D> Scissors;

    VkPipelineViewportStateCreateInfo ViewportStateCreateInfo;
    ViewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    ViewportStateCreateInfo.pNext = nullptr;
    ViewportStateCreateInfo.flags = {};
    ViewportStateCreateInfo.viewportCount = static_cast<uint32>(Viewports.size());
    ViewportStateCreateInfo.pViewports = Viewports.data();
    ViewportStateCreateInfo.scissorCount = static_cast<uint32>(Scissors.size());
    ViewportStateCreateInfo.pScissors = Scissors.data();


    VkPipelineRasterizationStateCreateInfo RasterizationStateCreateInfo{};
    RasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    RasterizationStateCreateInfo.pNext = nullptr;
    RasterizationStateCreateInfo.flags = {};
    RasterizationStateCreateInfo.depthClampEnable = false;
    RasterizationStateCreateInfo.rasterizerDiscardEnable = false;
    RasterizationStateCreateInfo.polygonMode = VK_POLYGON_MODE_FILL;
    RasterizationStateCreateInfo.cullMode = VK_CULL_MODE_BACK_BIT | VK_CULL_MODE_FRONT_BIT;
    RasterizationStateCreateInfo.frontFace = VK_FRONT_FACE_CLOCKWISE;
    RasterizationStateCreateInfo.depthBiasEnable = false;
    RasterizationStateCreateInfo.depthBiasConstantFactor = 0.f;
    RasterizationStateCreateInfo.depthBiasClamp = 0.f;
    RasterizationStateCreateInfo.depthBiasSlopeFactor = 0.f;
    RasterizationStateCreateInfo.lineWidth = 0.f;

    VkSampleMask SampleMask;

    VkPipelineMultisampleStateCreateInfo MultisampleStateCreateInfo{};
    MultisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    MultisampleStateCreateInfo.pNext = nullptr;
    MultisampleStateCreateInfo.flags = {};
    MultisampleStateCreateInfo.rasterizationSamples = VkSampleCountFlagBits::VK_SAMPLE_COUNT_2_BIT;
    MultisampleStateCreateInfo.sampleShadingEnable = false;
    MultisampleStateCreateInfo.minSampleShading = 0.f;
    MultisampleStateCreateInfo.pSampleMask = &SampleMask;
    MultisampleStateCreateInfo.alphaToCoverageEnable = false;
    MultisampleStateCreateInfo.alphaToOneEnable = false;

    VkStencilOpState Front;
    VkStencilOpState Back;

    VkPipelineDepthStencilStateCreateInfo DepthStencilStateCreateInfo;
    DepthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    DepthStencilStateCreateInfo.pNext = nullptr;
    DepthStencilStateCreateInfo.flags;
    DepthStencilStateCreateInfo.depthTestEnable = false;
    DepthStencilStateCreateInfo.depthWriteEnable = false;
    DepthStencilStateCreateInfo.depthCompareOp = VkCompareOp::VK_COMPARE_OP_ALWAYS;
    DepthStencilStateCreateInfo.depthBoundsTestEnable = false;
    DepthStencilStateCreateInfo.stencilTestEnable = false;
    DepthStencilStateCreateInfo.front = Front;
    DepthStencilStateCreateInfo.back = Back;
    DepthStencilStateCreateInfo.minDepthBounds = 0.f;
    DepthStencilStateCreateInfo.maxDepthBounds = 1.f;

    const TVector<VkPipelineColorBlendAttachmentState> ColorBlendAttachments;
    TArray<float, 4> BlendConstants;

    VkPipelineColorBlendStateCreateInfo ColorBlendStateCreateInfo{};
    ColorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    ColorBlendStateCreateInfo.pNext = nullptr;
    ColorBlendStateCreateInfo.flags = {};
    ColorBlendStateCreateInfo.logicOpEnable = false;
    ColorBlendStateCreateInfo.logicOp = VK_LOGIC_OP_AND;
    ColorBlendStateCreateInfo.attachmentCount = static_cast<uint32>(ColorBlendAttachments.size());
    ColorBlendStateCreateInfo.pAttachments = ColorBlendAttachments.data();
    ColorBlendStateCreateInfo.blendConstants[4];

    TVector<VkDynamicState> DynamicStates;

    VkPipelineDynamicStateCreateInfo DynamicStateCreateInfo{};
    DynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    DynamicStateCreateInfo.pNext = nullptr;
    DynamicStateCreateInfo.flags = {};
    DynamicStateCreateInfo.dynamicStateCount = static_cast<uint32>(DynamicStates.size());
    DynamicStateCreateInfo.pDynamicStates = DynamicStates.data();

    VkGraphicsPipelineCreateInfo PipelineCreateInfo{};
    PipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    PipelineCreateInfo.pNext = nullptr;
    PipelineCreateInfo.flags;
    PipelineCreateInfo.stageCount = static_cast<uint32>(ShaderStageCreateInfos.size());
    PipelineCreateInfo.pStages = ShaderStageCreateInfos.data();
    PipelineCreateInfo.pVertexInputState = &VertexInputStateCreateInfo;
    PipelineCreateInfo.pInputAssemblyState = &InputAssemblyStateCreateInfo;
    PipelineCreateInfo.pTessellationState = &TessellationStateCreateInfo;
    PipelineCreateInfo.pViewportState = &ViewportStateCreateInfo;
    PipelineCreateInfo.pRasterizationState = &RasterizationStateCreateInfo;
    PipelineCreateInfo.pMultisampleState = &MultisampleStateCreateInfo;
    PipelineCreateInfo.pDepthStencilState = &DepthStencilStateCreateInfo;
    PipelineCreateInfo.pColorBlendState = &ColorBlendStateCreateInfo;
    PipelineCreateInfo.pDynamicState = &DynamicStateCreateInfo;
    PipelineCreateInfo.layout = InLayout.GetHandle();
    PipelineCreateInfo.renderPass = InInitializer.RenderPass->GetHandle();
    PipelineCreateInfo.subpass = InInitializer.SubpassIndex;
    PipelineCreateInfo.basePipelineHandle = VK_NULL_HANDLE;
    PipelineCreateInfo.basePipelineIndex = -1;

    const VkResult GraphicsPipelineCreationResult = vkCreateGraphicsPipelines(GetDevice().GetHandle(), InCache.GetHandle(), 1, &_PipelineCreateInfo, nullptr, &_Handle);

    if (GraphicsPipelineCreationResult == VK_SUCCESS)
    {
        return true;
    }

    return false;
}

void Kanas::Core::FGraphicsPipeline::CmdBind(FCommandBuffer& InRecorder)
{
    vkCmdBindPipeline(InRecorder.GetHandle(), VK_PIPELINE_BIND_POINT_GRAPHICS, GetHandle());
}

void Kanas::Core::FGraphicsPipeline::CmdDraw(FCommandBuffer& InRecorder, uint32 InVertexCount, uint32 InInstanceCount, uint32 InFirstVertex, uint32 InFirstInstance)
{
    vkCmdDraw(InRecorder.GetHandle(), InVertexCount, InInstanceCount, InFirstVertex, InFirstInstance);
}

void Kanas::Core::FGraphicsPipeline::CmdDrawIndirect(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint64 InOffset, uint32 InDrawCount, uint32 InStride)
{
    vkCmdDrawIndirect(InRecorder.GetHandle(), InBuffer.GetHandle(), InOffset, InDrawCount, InStride);
}

void Kanas::Core::FGraphicsPipeline::CmdDrawIndirectCount(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint32 InOffset, FBuffer& InCountBuffer, uint64 InCountOffset, uint32 InMaxDrawCount, uint32 InStride)
{
    vkCmdDrawIndirectCount(InRecorder.GetHandle(), InBuffer.GetHandle(), InOffset, InCountBuffer.GetHandle(), InCountOffset, InMaxDrawCount, InStride);
}

void Kanas::Core::FGraphicsPipeline::CmdDrawIndexed(FCommandBuffer& InRecorder, uint32 InIndexCount, uint32 InInstanceCount, uint32 InFirstIndex, uint32 InVertexOffset, uint32 InFirstInstance)
{
    vkCmdDrawIndexed(InRecorder.GetHandle(), InIndexCount, InInstanceCount, InFirstIndex, InVertexOffset, InFirstIndex);
}

void Kanas::Core::FGraphicsPipeline::CmdDrawIndexedIndirect(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint64 InOffset, uint32 InDrawCount, uint32 InStride)
{
    vkCmdDrawIndexedIndirect(InRecorder.GetHandle(), InBuffer.GetHandle(), InOffset, InDrawCount, InStride);
}

void Kanas::Core::FGraphicsPipeline::CmdDrawIndexedIndirectCount(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint64 InOffset, FBuffer& InCountBuffer, uint64 InCountOffset, uint32 InMaxDrawCount, uint32 InStride)
{
    vkCmdDrawIndexedIndirectCount(InRecorder.GetHandle(), InBuffer.GetHandle(), InOffset, InCountBuffer.GetHandle(), InCountOffset, InMaxDrawCount, InStride);
}

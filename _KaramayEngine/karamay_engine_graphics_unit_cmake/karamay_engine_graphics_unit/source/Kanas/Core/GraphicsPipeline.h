#ifndef _GRAPHICS_PIPELINE_H_
#define _GRAPHICS_PIPELINE_H_

#include "Pipeline.h"

_KANAS_CORE_BEGIN

class RenderPass;


struct GraphicsPipelineStateInitializer
{
	RenderPass RenderPass;
	uint32 SubpassIndex;
};

class GraphicsPipeline final : public Pipeline
{
public:

	GraphicsPipeline(Device& InDevice);

	virtual ~GraphicsPipeline();

	bool Allocate(PipelineCache& InCache, PipelineLayout& InLayout, const GraphicsPipelineStateInitializer& InInitializer);

	static void AllocateCollection(const std::vector<GraphicsPipeline>& OutPipelines, Device& InDevice);

	virtual void CmdBind(CommandBuffer& InRecorder) override;

	static void CmdDraw(CommandBuffer& InRecorder, uint32 InVertexCount, uint32 InInstanceCount, uint32 InFirstVertex, uint32 InFirstInstance);

	static void CmdDrawIndirect(CommandBuffer& InRecorder, Buffer& InBuffer, uint64 InSize, uint32 InDrawCount, uint32 InStride);

	static void CmdDrawIndirectCount(CommandBuffer& InRecorder, Buffer& InBuffer, uint32 InOffset, Buffer& InCountBuffer, uint64 InCountOffset, uint32 InMaxDrawCount, uint32 InStride);

	static void CmdDrawIndexed(CommandBuffer& InRecorder, uint32 InIndexCount, uint32 InInstanceCount, uint32 InFirstIndex, uint32 InVertexOffset, uint32 InFirstInstance);

	static void CmdDrawIndexedIndirect(CommandBuffer& InRecorder, Buffer& InBuffer, uint64 InSize, uint32 InDrawCount, uint32 InStride);

	static void CmdDrawIndexedIndirectCount(CommandBuffer& InRecorder, Buffer& InBuffer, uint64 InOffset, Buffer& InCountBuffer, uint64 InCountOffset, uint32 InMaxDrawCount, uint32 InStride);

};

_KANAS_CORE_END

#endif
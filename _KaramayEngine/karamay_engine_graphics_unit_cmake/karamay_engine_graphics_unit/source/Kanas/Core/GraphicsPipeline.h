#ifndef _GRAPHICS_PIPELINE_H_
#define _GRAPHICS_PIPELINE_H_

#include "Pipeline.h"

_KANAS_CORE_BEGIN

class FRenderPass;
class FVertexShader;
class FTessellationControlShader;
class FTessellationEvaluationShader;
class FGeometryShader;
class FFragmentShader;

class FMeshShader;

struct FGraphicsPipelineStateInitializer
{
	TSharedPtr<FRenderPass> RenderPass;
	uint32 SubpassIndex;

	TSharedPtr<FVertexShader> VertexShader{};
	TSharedPtr<FTessellationControlShader> TescShader{};
	TSharedPtr<FTessellationEvaluationShader> TeseShader{};
	TSharedPtr<FGeometryShader> GeometryShader{};
	TSharedPtr<FFragmentShader> FragmentShader{};
};

class FGraphicsPipeline final : public FPipeline
{
	friend class FDevice;

	bool Allocate(const FGraphicsPipelineStateInitializer& InInitializer, TSharedPtr<FPipelineCache> InCache, TSharedPtr<FPipelineLayout> InLayout);

public:

	FGraphicsPipeline(FDevice& InDevice);

	virtual ~FGraphicsPipeline();

	virtual void CmdBind(FCommandBuffer& InRecorder) override;

	static void CmdDraw(FCommandBuffer& InRecorder, uint32 InVertexCount, uint32 InInstanceCount, uint32 InFirstVertex, uint32 InFirstInstance);

	static void CmdDrawIndirect(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint64 InSize, uint32 InDrawCount, uint32 InStride);

	static void CmdDrawIndirectCount(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint32 InOffset, FBuffer& InCountBuffer, uint64 InCountOffset, uint32 InMaxDrawCount, uint32 InStride);

	static void CmdDrawIndexed(FCommandBuffer& InRecorder, uint32 InIndexCount, uint32 InInstanceCount, uint32 InFirstIndex, uint32 InVertexOffset, uint32 InFirstInstance);

	static void CmdDrawIndexedIndirect(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint64 InSize, uint32 InDrawCount, uint32 InStride);

	static void CmdDrawIndexedIndirectCount(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint64 InOffset, FBuffer& InCountBuffer, uint64 InCountOffset, uint32 InMaxDrawCount, uint32 InStride);

};

_KANAS_CORE_END

#endif
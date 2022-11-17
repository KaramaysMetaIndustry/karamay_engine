#ifndef _GRAPHICS_PIPELINE_H_
#define _GRAPHICS_PIPELINE_H_

#include "Pipeline.h"

_KANAS_CORE_BEGIN

class FRenderPass;
class FShader;
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

	void GetShaders(TVector<TSharedPtr<FShader>>& OutShaders) const;
};

class FGraphicsPipeline final : public FPipeline
{
	friend class FDevice;

	bool Allocate(const FGraphicsPipelineStateInitializer& InInitializer, 
		TSharedPtr<FPipelineLayout> InLayout, 
		TSharedPtr<FPipelineCache> InCache = nullptr
	);

public:

	FGraphicsPipeline(FDevice& InDevice);

	FGraphicsPipeline(const FGraphicsPipeline&) = delete;
	FGraphicsPipeline& operator=(const FGraphicsPipeline&) = delete;

	FGraphicsPipeline(FGraphicsPipeline&& Other);

	virtual ~FGraphicsPipeline() override;


	void CmdBindIndexBuffer(FCommandBuffer& InRecorder, TSharedPtr<FIndexBuffer> IndexBuffer);

	void CmdBindVertexBuffers(FCommandBuffer& InRecorder, uint32 Binding, TSharedPtr<FVertexBuffer> VertexBuffer, uint64 Offset);


	void CmdDraw(FCommandBuffer& InRecorder, uint32 InVertexCount, uint32 InInstanceCount, uint32 InFirstVertex, uint32 InFirstInstance);

	void CmdDrawIndirect(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint64 InSize, uint32 InDrawCount, uint32 InStride);

	void CmdDrawIndirectCount(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint32 InOffset, FBuffer& InCountBuffer, uint64 InCountOffset, uint32 InMaxDrawCount, uint32 InStride);

	void CmdDrawIndexed(FCommandBuffer& InRecorder, uint32 InIndexCount, uint32 InInstanceCount, uint32 InFirstIndex, uint32 InVertexOffset, uint32 InFirstInstance);

	void CmdDrawIndexedIndirect(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint64 InSize, uint32 InDrawCount, uint32 InStride);

	void CmdDrawIndexedIndirectCount(FCommandBuffer& InRecorder, FBuffer& InBuffer, uint64 InOffset, FBuffer& InCountBuffer, uint64 InCountOffset, uint32 InMaxDrawCount, uint32 InStride);

};

_KANAS_CORE_END

#endif
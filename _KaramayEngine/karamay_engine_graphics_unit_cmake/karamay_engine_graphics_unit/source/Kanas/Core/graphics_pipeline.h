#ifndef _GRAPHICS_PIPELINE_H_
#define _GRAPHICS_PIPELINE_H_

#include "Pipeline.h"

_KANAS_CORE_BEGIN

class render_pass;
class shader;
class FVertexShader;
class FTessellationControlShader;
class FTessellationEvaluationShader;
class FGeometryShader;
class FFragmentShader;

class FMeshShader;

struct graphics_pipelineStateinitializer
{
	std::shared_ptr<render_pass> RenderPass;
	std::uint32_t SubpassIndex;

	std::shared_ptr<FVertexShader> VertexShader{};
	std::shared_ptr<FTessellationControlShader> TescShader{};
	std::shared_ptr<FTessellationEvaluationShader> TeseShader{};
	std::shared_ptr<FGeometryShader> GeometryShader{};
	std::shared_ptr<FFragmentShader> FragmentShader{};

	void GetShaders(std::vector<std::shared_ptr<shader>>& OutShaders) const;
};

class graphics_pipeline final : public pipeline
{
	friend class device;

	bool alllocate(const graphics_pipelineStateinitializer& Ininitializer, 
		std::shared_ptr<pipeline_layout> InLayout, 
		std::shared_ptr<pipeline_cache> InCache = nullptr
	);

public:

	graphics_pipeline(device& owner);

	graphics_pipeline(const graphics_pipeline&) = delete;
	graphics_pipeline& operator=(const graphics_pipeline&) = delete;

	graphics_pipeline(graphics_pipeline&& Other);

	virtual ~graphics_pipeline() override;


	void CmdBindIndexBuffer(command_buffer& InRecorder, std::shared_ptr<FIndexBuffer> IndexBuffer);

	void CmdBindVertexBuffers(command_buffer& InRecorder, std::uint32_t Binding, std::shared_ptr<FVertexBuffer> VertexBuffer, std::uint64_t Offset);


	void CmdDraw(command_buffer& InRecorder, std::uint32_t InVertexCount, std::uint32_t InInstanceCount, std::uint32_t InFirstVertex, std::uint32_t InFirstInstance);

	void CmdDrawIndirect(command_buffer& InRecorder, buffer& InBuffer, std::uint64_t InSize, std::uint32_t InDrawCount, std::uint32_t InStride);

	void CmdDrawIndirectCount(command_buffer& InRecorder, buffer& InBuffer, std::uint32_t InOffset, buffer& InCountBuffer, std::uint64_t InCountOffset, std::uint32_t InMaxDrawCount, std::uint32_t InStride);

	void CmdDrawIndexed(command_buffer& InRecorder, std::uint32_t InIndexCount, std::uint32_t InInstanceCount, std::uint32_t InFirstIndex, std::uint32_t InVertexOffset, std::uint32_t InFirstInstance);

	void CmdDrawIndexedIndirect(command_buffer& InRecorder, buffer& InBuffer, std::uint64_t InSize, std::uint32_t InDrawCount, std::uint32_t InStride);

	void CmdDrawIndexedIndirectCount(command_buffer& InRecorder, buffer& InBuffer, std::uint64_t InOffset, buffer& InCountBuffer, std::uint64_t InCountOffset, std::uint32_t InMaxDrawCount, std::uint32_t InStride);

};

_KANAS_CORE_END

#endif
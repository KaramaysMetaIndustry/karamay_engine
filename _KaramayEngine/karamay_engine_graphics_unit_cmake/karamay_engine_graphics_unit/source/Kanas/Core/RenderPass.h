#ifndef _RENDER_PASS_H_
#define _RENDER_PASS_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class CommandBuffer;
class Framebuffer;

class RenderPass final : public DeviceObject<VkRenderPass>
{
public:

	RenderPass(Device& InDevice);

	virtual ~RenderPass() override;

	bool Allocate(const std::vector<VkAttachmentDescription>& InAttachments, const std::vector<VkSubpassDescription>& InSubpasses, const std::vector<VkSubpassDependency>& InSubpassDependencies);

	using CmdSequence = std::function<void(CommandBuffer&, Framebuffer&)>;

	void CmdCollect(CommandBuffer& InRecorder);

	Framebuffer* GetFramebuffer() const;

	uint32 NumOfSubpasses() const;

	std::vector<VkClearValue> ClearValues;

	VkRect2D RenderArea;
	
	VkSubpassContents SubpassContents;
	
	CmdSequence Sequence;

private:

	Framebuffer* RenderTarget;

};

_KANAS_CORE_END

#endif
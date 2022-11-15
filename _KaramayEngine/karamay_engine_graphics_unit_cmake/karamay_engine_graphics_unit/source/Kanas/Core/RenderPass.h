#ifndef _RENDER_PASS_H_
#define _RENDER_PASS_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FCommandBuffer;
class FFramebuffer;

class FRenderPass final : public FDeviceObject<VkRenderPass>
{

	bool Allocate(const TVector<VkAttachmentDescription>& InAttachments, const TVector<VkSubpassDescription>& InSubpasses, const TVector<VkSubpassDependency>& InSubpassDependencies);

public:

	FRenderPass(FDevice& InDevice);

	virtual ~FRenderPass() override;


	using CmdSequence = std::function<void(FCommandBuffer&, FFramebuffer&)>;

	void CmdCollect(FCommandBuffer& InRecorder);

	TVector<VkClearValue> ClearValues;

	VkRect2D RenderArea;
	
	VkSubpassContents SubpassContents;
	
	CmdSequence Sequence;

private:

	TUniquePtr<FFramebuffer> Framebuffer;

};

_KANAS_CORE_END

#endif
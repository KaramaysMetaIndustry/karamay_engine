#ifndef _RENDER_PASS_H_
#define _RENDER_PASS_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FCommandBuffer;
class FFramebuffer;
class FSubpass;
class FAttachment;

class FRenderPass final : public FDeviceObject<VkRenderPass>
{
	friend class FDeivce;

	using SubpassCreation = std::function<bool(const FFramebuffer& InFramebuffer, TVector<TUniquePtr<FSubpass>>& SubpassesToRegister)>;

	bool Allocate(const TVector<TSharedPtr<FSubpass>>& InSubpasses, const TVector<VkSubpassDependency>& InSubpassDependencies);

	bool Allocate(
		const TVector<TSharedPtr<FAttachmentView>>& Attachments, 
		const SubpassCreation& SubpassCreationLambda, 
		const FFramebufferDimension& FramebufferDimension
	);

public:

	FRenderPass(FDevice& InDevice);

	virtual ~FRenderPass() override;

	void CmdCollect(FCommandBuffer& InRecorder);

	TVector<VkClearValue> ClearValues;

	VkRect2D RenderArea;

	VkSubpassContents SubpassContents;
	
	using CmdSequence = std::function<void(FCommandBuffer&, FFramebuffer&)>;

	CmdSequence Sequence;

private:

	TSharedPtr<FSubpass> DefaultSubpass;

	TUniquePtr<FFramebuffer> Framebuffer;

public:

	void CreateDefaultSubpass();

	TSharedPtr<FSubpass> GetDefaultSubpass() const
	{
		return DefaultSubpass;
	}

	TSharedPtr<FSubpass> GetFinalSubpass() const;

};

_KANAS_CORE_END

#endif
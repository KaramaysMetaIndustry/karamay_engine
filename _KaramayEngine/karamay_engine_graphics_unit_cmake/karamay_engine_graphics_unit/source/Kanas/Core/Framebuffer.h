#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FImageView;
class FRenderPass;
class FAttachment;

class FFramebuffer final : public FDeviceObject<VkFramebuffer>
{
	friend class FRenderPass;

	bool Allocate(const FRenderPass& RenderPass, const FFramebufferDimension& Dimension, const TVector<TSharedPtr<FImageView>>& AttachmentImageViews);

public:

	FFramebuffer(FDevice& InDevice);

	FFramebuffer(const FFramebuffer&) = delete;
	FFramebuffer(FFramebuffer&& Other);

	FFramebuffer& operator=(const FFramebuffer&) = delete;

	virtual ~FFramebuffer();

	void GetAttachments(TVector<TSharedPtr<FAttachment>>& OutAttachments);

private:

	TVector<TSharedPtr<FImageView>> Attachments;

};

_KANAS_CORE_END

#endif
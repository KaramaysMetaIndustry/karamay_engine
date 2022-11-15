#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FImageView;
class FRenderPass;

class FFramebuffer final : public FDeviceObject<VkFramebuffer>
{
	friend class FDevice;

	bool Allocate(TSharedPtr<FRenderPass> RenderPass, uint32 Width, uint32 Height, uint32 Layers, const TVector<TSharedPtr<FImageView>>& InAttachments);

public:

	FFramebuffer(FDevice& InDevice);

	FFramebuffer(const FFramebuffer&) = delete;
	FFramebuffer(FFramebuffer&& Other);

	FFramebuffer& operator=(const FFramebuffer&) = delete;

	virtual ~FFramebuffer();

private:

	TSharedPtr<FRenderPass> Owner;

	TVector<TSharedPtr<FImageView>> Attachments;


};

_KANAS_CORE_END

#endif
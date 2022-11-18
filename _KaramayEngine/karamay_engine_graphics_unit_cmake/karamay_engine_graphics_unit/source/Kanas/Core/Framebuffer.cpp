#include "Framebuffer.h"
#include "Device.h"
#include "ImageView.h"
#include "RenderPass.h"

struct FFramebufferStaticHelper
{
	static void Create();

};

bool Kanas::Core::FFramebuffer::Allocate(const FRenderPass& RenderPass, const FFramebufferDimension& Dimension, const TVector<TSharedPtr<FImageView>>& AttachmentImageViews)
{
	TVector<VkImageView> RawImageViews;
	RawImageViews.reserve(AttachmentImageViews.size());

	for (const auto& AttachmentImageView : AttachmentImageViews)
	{
		if (AttachmentImageView)
		{
			RawImageViews.emplace_back(AttachmentImageView->GetHandle());
		}
	}

	VkFramebufferCreateInfo FramebufferCreateInfo{};
	FramebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	FramebufferCreateInfo.pNext = nullptr;
	FramebufferCreateInfo.flags = {};
	FramebufferCreateInfo.renderPass = RenderPass.GetHandle();
	FramebufferCreateInfo.attachmentCount = static_cast<uint32>(RawImageViews.size());
	FramebufferCreateInfo.pAttachments = RawImageViews.data();
	FramebufferCreateInfo.width = Width;
	FramebufferCreateInfo.height = Height;
	FramebufferCreateInfo.layers = Layers;

	const VkResult Result = vkCreateFramebuffer(GetDevice().GetHandle(), &FramebufferCreateInfo, nullptr, &_Handle);

	if (Result == VkResult::VK_SUCCESS)
	{
		Attachments = AttachmentImageViews;

		return true;
	}

	return false;
}

Kanas::Core::FFramebuffer::FFramebuffer(FDevice& InDevice) :
	FDeviceObject(InDevice)
{
}

Kanas::Core::FFramebuffer::FFramebuffer(FFramebuffer&& Other) :
	FDeviceObject(Other.GetDevice())
{
}

Kanas::Core::FFramebuffer::~FFramebuffer()
{
	if (IsValid())
	{
		vkDestroyFramebuffer(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}


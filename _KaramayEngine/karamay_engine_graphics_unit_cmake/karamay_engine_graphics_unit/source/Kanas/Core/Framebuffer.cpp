#include "Framebuffer.h"
#include "Device.h"
#include "ImageView.h"
#include "RenderPass.h"

bool Kanas::Core::FFramebuffer::Allocate(TSharedPtr<FRenderPass> RenderPass, uint32 Width, uint32 Height,uint32 Layers, const TVector<TSharedPtr<FImageView>>& InAttachments)
{
	if (!RenderPass)
	{
		return false;
	}

	VkFramebufferCreateFlagBits::VK_FRAMEBUFFER_CREATE_IMAGELESS_BIT; // imageless

	VkFramebufferCreateInfo FramebufferCreateInfo{};
	FramebufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	FramebufferCreateInfo.pNext = nullptr;
	FramebufferCreateInfo.flags = {};
	FramebufferCreateInfo.renderPass = RenderPass->GetHandle();

	TVector<VkImageView> ImageViewHandles;
	ImageViewHandles.reserve(InAttachments.size());

	for (const auto& Attachment : InAttachments)
	{
		if (Attachment)
		{
			ImageViewHandles.emplace_back(Attachment->GetHandle());
		}
	}

	FramebufferCreateInfo.attachmentCount = static_cast<uint32>(ImageViewHandles.size());
	FramebufferCreateInfo.pAttachments = ImageViewHandles.data();
	FramebufferCreateInfo.width = Width;
	FramebufferCreateInfo.height = Height;
	FramebufferCreateInfo.layers = Layers;

	const VkResult FramebufferCreationResult = vkCreateFramebuffer(GetDevice().GetHandle(), &FramebufferCreateInfo, nullptr, &_Handle);

	if (FramebufferCreationResult == VkResult::VK_SUCCESS)
	{
		Attachments = InAttachments;

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


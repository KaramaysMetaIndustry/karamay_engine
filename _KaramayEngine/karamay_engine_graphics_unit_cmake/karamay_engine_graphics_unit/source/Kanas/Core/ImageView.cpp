#include "ImageView.h"
#include "Image.h"
#include "Device.h"

bool Kanas::Core::FImageView::Allocate(TSharedPtr<FImage> InImage, VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange)
{
	if (!InImage)
	{
		return false;
	}

	VkImageViewCreateInfo ImageViewCreateInfo;
	ImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	ImageViewCreateInfo.pNext = nullptr;
	ImageViewCreateInfo.flags = {};
	ImageViewCreateInfo.image = InImage->GetHandle();
	ImageViewCreateInfo.viewType = InViewType;
	ImageViewCreateInfo.format = InFormat;
	ImageViewCreateInfo.components = InComponents;
	ImageViewCreateInfo.subresourceRange = InSubresourceRange;

	const VkResult Result = vkCreateImageView(GetDevice().GetHandle(), &ImageViewCreateInfo, nullptr, &_Handle);

	if (Result == VkResult::VK_SUCCESS)
	{
		Image = InImage;
		return true;
	}

	return false;
}

Kanas::Core::FImageView::FImageView(FDevice& InDevice) :
	FDeviceObject(InDevice)
{
}

Kanas::Core::FImageView::FImageView(FImageView&& Other) :
	FDeviceObject(Other.GetDevice())
{
	_Handle = Other.GetHandle();
	Other.ResetHandle();
}

Kanas::Core::FImageView::~FImageView()
{
	if (IsValid())
	{
		vkDestroyImageView(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}


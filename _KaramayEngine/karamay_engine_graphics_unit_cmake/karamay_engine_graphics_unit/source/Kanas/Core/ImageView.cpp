#include "ImageView.h"
#include "Image.h"
#include "Device.h"

Kanas::Core::ImageView::ImageView(Device& InDevice) :
	DeviceObject(InDevice)
{
}

Kanas::Core::ImageView::~ImageView()
{
	if (IsValid())
	{
		vkDestroyImageView(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

bool Kanas::Core::ImageView::Allocate(Image* InImage, VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange)
{
	VkImageViewCreateInfo ImageViewCreateInfo;
	ImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	ImageViewCreateInfo.pNext = nullptr;
	ImageViewCreateInfo.flags = {};
	ImageViewCreateInfo.image = InImage->GetHandle();
	ImageViewCreateInfo.viewType = InViewType;
	ImageViewCreateInfo.format = InFormat;
	ImageViewCreateInfo.components = InComponents;
	ImageViewCreateInfo.subresourceRange = InSubresourceRange;

	VkResult Result = vkCreateImageView(GetDevice().GetHandle(), &ImageViewCreateInfo, nullptr, &_Handle);
	
	if (Result == VkResult::VK_SUCCESS)
	{
		Target = InImage;
		return true;
	}

	return false;
}

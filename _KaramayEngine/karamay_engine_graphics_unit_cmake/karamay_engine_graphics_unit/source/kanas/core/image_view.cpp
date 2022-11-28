#include "image_view.h"
#include "image.h"
#include "device.h"

bool kanas::core::image_view::alllocate(std::shared_ptr<image> InImage, VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange)
{
	if (!InImage)
	{
		return false;
	}

	VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DEFERRED_BIT_EXT; // FragmentDensityMapDeferred
	VK_IMAGE_VIEW_CREATE_FRAGMENT_DENSITY_MAP_DYNAMIC_BIT_EXT; // FragmentDensityMapDynamic

	VkImageViewCreateInfo ImageViewCreateInfo{};
	ImageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	ImageViewCreateInfo.pNext = nullptr;
	ImageViewCreateInfo.flags = {};
	ImageViewCreateInfo.image = InImage->get_handle();
	ImageViewCreateInfo.viewType = InViewType;
	ImageViewCreateInfo.format = InFormat;
	ImageViewCreateInfo.components = InComponents;
	ImageViewCreateInfo.subresourceRange = InSubresourceRange;

	const VkResult Result = vkCreateImageView(get_device().get_handle(), &ImageViewCreateInfo, nullptr, &handle);

	if (Result == VkResult::VK_SUCCESS)
	{
		Image = InImage;

		return true;
	}

	return false;
}

kanas::core::image_view::image_view(device& owner) :
	device_object(owner)
{
}

kanas::core::image_view::image_view(image_view&& Other) :
	device_object(Other.get_device())
{
	handle = Other.get_handle();

	Other.reset_handle();
}

kanas::core::image_view::~image_view()
{
	if (IsValid())
	{
		vkDestroyImageView(get_device().get_handle(), get_handle(), nullptr);

		reset_handle();
	}
}


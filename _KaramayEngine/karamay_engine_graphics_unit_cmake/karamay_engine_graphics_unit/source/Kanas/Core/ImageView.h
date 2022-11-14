#ifndef _IMAGE_VIEW_H_
#define _IMAGE_VIEW_H_


#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class Image;

class ImageView final : public DeviceObject<VkImageView>
{
public:
	
	ImageView(Device& InDevice);

	ImageView(const ImageView& Other) = delete;
	ImageView(ImageView&& Other);

	ImageView& operator=(const ImageView& Other) = delete;

	virtual ~ImageView() override;

	bool Allocate(TSharedPtr<Image> InImage, VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange);

private:

	TSharedPtr<Image> Target;

};


_KANAS_CORE_END


#endif
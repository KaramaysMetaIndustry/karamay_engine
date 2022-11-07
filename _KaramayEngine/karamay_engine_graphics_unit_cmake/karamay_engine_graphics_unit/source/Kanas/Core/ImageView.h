#ifndef _IMAGE_VIEW_H_
#define _IMAGE_VIEW_H_


#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class Image;

class ImageView final : public DeviceObject<VkImageView>
{
public:
	
	ImageView(Device& InDevice);

	virtual ~ImageView() override;

	bool Allocate(Image* InImage, VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange);

private:

	Image* Target{ nullptr };

};


_KANAS_CORE_END


#endif
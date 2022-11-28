#ifndef _IMAGE_VIEW_H_
#define _IMAGE_VIEW_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class image;

class image_view final : public device_object<VkImageView>
{
	friend class device;

	bool alllocate(std::shared_ptr<image> InImage, VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange);

public:
	
	image_view(device& owner);

	image_view(const image_view& Other) = delete;
	image_view(image_view&& Other);

	image_view& operator=(const image_view& Other) = delete;

	virtual ~image_view() override;

private:

	std::shared_ptr<image> Image{};

	VkImageViewType ImageViewType{};

	VkFormat Format{};

public:

	std::shared_ptr<image> GetImage() const 
	{ 
		return Image; 
	}

	VkImageViewType GetViewType() const 
	{ 
		return ImageViewType; 
	}

	VkFormat GetViewFormat() const 
	{ 
		return Format; 
	}

};


_KANAS_CORE_END


#endif
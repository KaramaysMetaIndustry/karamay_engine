#ifndef _IMAGE_VIEW_H_
#define _IMAGE_VIEW_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FImage;

class FImageView final : public FDeviceObject<VkImageView>
{
	friend class FDevice;

	bool Allocate(TSharedPtr<FImage> InImage, VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange);

public:
	
	FImageView(FDevice& InDevice);

	FImageView(const FImageView& Other) = delete;
	FImageView(FImageView&& Other);

	FImageView& operator=(const FImageView& Other) = delete;

	virtual ~FImageView() override;

private:

	TSharedPtr<FImage> Image{};

	VkImageViewType ImageViewType{};

	VkFormat Format{};

public:

	TSharedPtr<FImage> GetImage() const 
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
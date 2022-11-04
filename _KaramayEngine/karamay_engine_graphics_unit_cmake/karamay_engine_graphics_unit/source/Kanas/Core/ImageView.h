#ifndef _IMAGE_VIEW_H_
#define _IMAGE_VIEW_H_


#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class Image;

class ImageView final : public DeviceObject<VkImageView>
{
public:
	
	ImageView();

	~ImageView();

public:



};


_KANAS_CORE_END


#endif
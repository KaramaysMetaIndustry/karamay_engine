#ifndef IMAGE_VIEW_H
#define IMAGE_VIEW_H
#include "device_object.h"

class image;

class image_view final : public device_object<VkImageView>
{
private:

	image* _target;

public:

	bool allocate(image* target);

	void deallocate();

};

#endif
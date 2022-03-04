#ifndef IMAGE_VIEW_H
#define IMAGE_VIEW_H
#include "device_object.h"

class image;

class image_view final : public device_object<VkImageView>
{
public:
	image_view(device& dev);

	image_view(const image_view&) = delete;
	image_view& operator=(const image_view&) = delete;

	~image_view();

private:

	image* _target;

public:

	bool allocate(image* target);

	void deallocate();

};

#endif
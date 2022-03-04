#ifndef BUFFER_VIEW_H
#define BUFFER_VIEW_H
#include "device_object.h"

class buffer;

class buffer_view final : public device_object<VkBufferView>
{
public:

	buffer_view(device& dev);

	buffer_view(const buffer_view&) = delete;
	buffer_view& operator=(const buffer_view&) = delete;

	~buffer_view() override;

private:

	buffer* _target = nullptr;

	VkFormat _format;

	uint64 _offset = 0;

	uint64 _range = 0;

public:

	bool allocate(buffer* target, uint64 offset, uint64 range, VkFormat format);

	void deallocate();

};

#endif
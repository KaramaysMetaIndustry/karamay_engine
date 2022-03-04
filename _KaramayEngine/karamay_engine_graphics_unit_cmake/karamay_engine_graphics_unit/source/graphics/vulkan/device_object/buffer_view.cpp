#include "buffer_view.h"
#include "buffer.h"

buffer_view::buffer_view(device& dev) : device_object(dev)
{
}

buffer_view::~buffer_view()
{
	deallocate();
}

bool buffer_view::allocate(buffer* target, uint64 offset, uint64 range, VkFormat format)
{
	VkBufferViewCreateInfo _create_info;
	_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
	_create_info.buffer = _target->handle();
	_create_info.format = format;
	_create_info.offset = offset;
	_create_info.range = range;

	vkCreateBufferView(_device.handle(), &_create_info, nullptr, &_handle);

	if (_handle == VK_NULL_HANDLE)
		return false;

	return true;
}

void buffer_view::deallocate()
{
	vkDestroyBufferView(_device.handle(), _handle, nullptr);
}


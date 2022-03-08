#include "buffer_view.h"
#include "buffer.h"

buffer_view::buffer_view(device& dev) : device_object(dev)
{
}

buffer_view::~buffer_view()
{
	deallocate();
}

bool buffer_view::allocate(std::shared_ptr<buffer> target, uint64 offset, uint64 range, VkFormat format) noexcept
{
	if (!target || range == 0)
	{
		return false;
	}

	deallocate();

	VkBufferViewCreateInfo _create_info{};
	_create_info.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
	_create_info.buffer = target->handle();
	_create_info.format = format;
	_create_info.offset = offset;
	_create_info.range = range;

	auto _result = vkCreateBufferView(_device.handle(), &_create_info, nullptr, &_handle);

	if (_result != VkResult::VK_SUCCESS || _handle == nullptr)
	{
		return false;
	}

	_target = target;

	return true;
}

void buffer_view::deallocate() noexcept
{
	if (_handle)
	{
		vkDestroyBufferView(_device.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}


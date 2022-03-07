#include "acceleration_structure.h"

acceleration_structure::acceleration_structure(device& dev) : device_object(dev)
{
}

acceleration_structure::~acceleration_structure()
{
	deallocate();
}

bool acceleration_structure::allocate() noexcept
{
	deallocate();

	VkAccelerationStructureCreateInfoKHR _create_info{};
	_create_info.sType;
	_create_info.buffer;
	_create_info.createFlags;
	_create_info.deviceAddress;
	_create_info.offset;
	_create_info.size;
	_create_info.type;

	auto _result = device_khr_func(vkCreateAccelerationStructureKHR)(_device.handle(), &_create_info, nullptr, &_handle);

	if (_result != VkResult::VK_SUCCESS)
	{
		return false;
	}

	return true;
}

void acceleration_structure::deallocate() noexcept
{
	if (_handle)
	{
		device_khr_func(vkDestroyAccelerationStructureKHR)(_device.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

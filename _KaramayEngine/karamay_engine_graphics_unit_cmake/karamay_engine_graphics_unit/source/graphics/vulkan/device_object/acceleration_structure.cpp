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
	return false;
}

void acceleration_structure::deallocate() noexcept
{
	if (_handle)
	{
		device_khr_func(vkDestroyAccelerationStructureKHR)(_device.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

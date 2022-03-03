#include "instance.h"

void instance::enumerate_physical_devices(std::vector<physical_device*>& physical_devices)
{
	uint32 _count = 0;
	vkEnumeratePhysicalDevices(_handle, &_count, nullptr);
	std::vector<VkPhysicalDevice> _pds(_count);
	physical_devices.reserve(_count);
	vkEnumeratePhysicalDevices(_handle, &_count, _pds.data());

	for (auto _pd : _pds)
	{
		physical_devices.push_back(new physical_device(_pd));
	}
}

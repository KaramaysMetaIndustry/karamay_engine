#ifndef QUEUE_H
#define QUEUE_H
#include "device_object.h"

class fence;

class queue final : public device_object<VkQueue>
{
public:

	bool allocate(uint32 queue_family_index, uint32 queue_index)
	{
		vkGetDeviceQueue(_device.handle(), queue_family_index, queue_index, &_handle);
	}

public:
	
	void submit(const VkSubmitInfo& submit, fence* f);

	void submit(const std::vector<VkSubmitInfo>& submits, fence* f);

	void present(VkPresentInfoKHR info)
	{
		vkQueuePresentKHR(_handle, &info);
	}

};

#endif
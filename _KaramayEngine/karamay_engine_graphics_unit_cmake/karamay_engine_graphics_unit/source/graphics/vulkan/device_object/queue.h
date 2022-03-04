#ifndef QUEUE_H
#define QUEUE_H
#include "device_object.h"

class queue final : public device_object<VkQueue>
{
public:

	bool allocate(uint32 queue_family_index, uint32 queue_index)
	{
		vkGetDeviceQueue(_device.handle(), queue_family_index, queue_index, &_handle);
	}

	void submit(std::vector<VkSubmitInfo>& submits, VkFence fence)
	{
		vkQueueSubmit(_handle, submits.size(), submits.data(), fence);
	}

};

#endif
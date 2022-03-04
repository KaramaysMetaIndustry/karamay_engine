#include "fence.h"

void fence::wait(bool wait_all, uint64 timeout)
{
	vkWaitForFences(_device.handle(), 1, &_handle, wait_all, timeout);
}

void fence::reset()
{
	vkResetFences(_device.handle(), 1, &_handle);
}

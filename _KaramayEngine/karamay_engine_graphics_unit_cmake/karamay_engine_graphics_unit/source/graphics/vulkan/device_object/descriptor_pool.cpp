#include "descriptor_pool.h"

void descriptor_pool::reset(VkDescriptorPoolResetFlags flags) noexcept
{
	vkResetDescriptorPool(_device.handle(), _handle, flags);
}

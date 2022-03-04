#include "queue.h"
#include "fence.h"

void queue::submit(const VkSubmitInfo& submit, fence* f)
{
}

void queue::submit(const std::vector<VkSubmitInfo>& submits, fence* f)
{
	vkQueueSubmit(_handle, submits.size(), submits.data(), f->handle());
}

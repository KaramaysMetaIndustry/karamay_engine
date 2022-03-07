#include "queue.h"
#include "fence.h"


queue::queue(device& dev) : device_object(dev)
{
}

queue::~queue()
{
}

bool queue::allocate(uint32 queue_family_index, uint32 queue_index) noexcept
{
	vkGetDeviceQueue(_device.handle(), queue_family_index, queue_index, &_handle);
	return true;
}

void queue::bind_sparse(const std::vector<VkBindSparseInfo>& bind_spare_infos, fence* f) noexcept
{
	vkQueueBindSparse(_handle, bind_spare_infos.size(), bind_spare_infos.data(), f->handle());
}

void queue::bind_sparse(const VkBindSparseInfo& bind_sparse_info, fence* f) noexcept
{
	vkQueueBindSparse(_handle, 1, &bind_sparse_info, f->handle());
}

void queue::present(const VkPresentInfoKHR& info) noexcept
{
	vkQueuePresentKHR(_handle, &info);
}

void queue::submit(const VkSubmitInfo& submit, fence* f) noexcept
{
	vkQueueSubmit(_handle, 1, &submit, f->handle());
}

void queue::submit(const std::vector<VkSubmitInfo>& submits, fence* f) noexcept
{
	vkQueueSubmit(_handle, submits.size(), submits.data(), f->handle());
}

void queue::wait() noexcept
{
	vkQueueWaitIdle(_handle);
}

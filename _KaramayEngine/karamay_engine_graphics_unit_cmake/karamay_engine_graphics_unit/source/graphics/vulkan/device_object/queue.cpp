#include "queue.h"
#include "fence.h"

vk_queue::vk_queue(vk_device& dev) : 
	device_object(dev)
{
}

vk_queue::~vk_queue()
{
}

bool vk_queue::allocate(uint32 queue_family_index, uint32 queue_index) noexcept
{
	vkGetDeviceQueue(_dev.handle(), queue_family_index, queue_index, &_handle);
	return true;
}

bool vk_queue::bind_sparse(const std::vector<VkBindSparseInfo>& bind_spare_infos, vk_fence* f) noexcept
{
	vkQueueBindSparse(_handle, bind_spare_infos.size(), bind_spare_infos.data(), f->handle());
	return true;
}

bool vk_queue::bind_sparse(const VkBindSparseInfo& bind_sparse_info, vk_fence* f) noexcept
{
	vkQueueBindSparse(_handle, 1, &bind_sparse_info, f->handle());
	return true;
}

bool vk_queue::present(const VkPresentInfoKHR& info) noexcept
{
	vkQueuePresentKHR(_handle, &info);
	return true;
}

void vk_queue::submit(const VkSubmitInfo& submit, vk_fence* f) noexcept
{
	vkQueueSubmit(_handle, 1, &submit, f->handle());
}

void vk_queue::submit(const std::vector<VkSubmitInfo>& submits, vk_fence* f) noexcept
{
	vkQueueSubmit(_handle, submits.size(), submits.data(), f->handle());
}

void vk_queue::wait() noexcept
{
	vkQueueWaitIdle(_handle);
}

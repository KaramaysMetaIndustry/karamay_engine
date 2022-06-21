#ifndef QUEUE_H
#define QUEUE_H
#include "device_object.h"

class vk_fence;

class vk_queue final : public device_object<VkQueue>
{
public:

	vk_queue(vk_device& dev);

	vk_queue(const vk_queue&) = delete;
	vk_queue& operator=(const vk_queue&) = delete;

	~vk_queue() override;

public:

	bool allocate(uint32 queue_family_index, uint32 queue_index) noexcept;

public:

	bool bind_sparse(const VkBindSparseInfo& bind_sparse_info, vk_fence* f) noexcept;

	bool bind_sparse(const std::vector<VkBindSparseInfo>& bind_spare_infos, vk_fence* f) noexcept;

	bool present(const VkPresentInfoKHR& info) noexcept;

	void submit(const VkSubmitInfo& submit, vk_fence* f) noexcept;

	void submit(const std::vector<VkSubmitInfo>& submits, vk_fence* f) noexcept;

	/*
	* block, wait the queue finished all submitions
	*/
	void wait() noexcept;

};

#endif
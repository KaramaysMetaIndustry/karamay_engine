#ifndef QUEUE_H
#define QUEUE_H
#include "device_object.h"

class fence;

class queue final : public device_object<VkQueue>
{
public:

	queue(device& dev);

	queue(const queue&) = delete;
	queue& operator=(const queue&) = delete;

	~queue() override;

public:

	bool allocate(uint32 queue_family_index, uint32 queue_index) noexcept;

public:

	bool bind_sparse(const VkBindSparseInfo& bind_sparse_info, fence* f) noexcept;

	bool bind_sparse(const std::vector<VkBindSparseInfo>& bind_spare_infos, fence* f) noexcept;

	bool present(const VkPresentInfoKHR& info) noexcept;

	void submit(const VkSubmitInfo& submit, fence* f) noexcept;

	void submit(const std::vector<VkSubmitInfo>& submits, fence* f) noexcept;

	/*
	* block, wait the queue finished all submitions
	*/
	void wait() noexcept;

};

#endif
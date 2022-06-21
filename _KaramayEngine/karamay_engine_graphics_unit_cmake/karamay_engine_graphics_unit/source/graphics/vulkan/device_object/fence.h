#ifndef FENCE_H
#define FENCE_H
#include "device_object.h"

class vk_fence final : public device_object<VkFence>
{
public:
	vk_fence(device& dev);

	vk_fence(const vk_fence&) = delete;
	vk_fence& operator=(const vk_fence&) = delete;

	~vk_fence() override;

public:

	/*
	* block the thread
	* unsignaled -> signaled
	*/
	void wait(bool wait_all, uint64 timeout) noexcept;

	/*
	* non-block, for epoll
	*/
	bool is_signaled() noexcept;

	/*
	* reset to unsignaled
	*/
	void reset() noexcept;

public:

	bool allocate() noexcept;

	void deallocate() noexcept;

};


#endif
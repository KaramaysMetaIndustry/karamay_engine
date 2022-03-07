#ifndef FENCE_H
#define FENCE_H
#include "device_object.h"

class fence final : public device_object<VkFence>
{
public:
	fence(device& dev);

	fence(const fence&) = delete;
	fence& operator=(const fence&) = delete;

	~fence() override;

public:

	bool allocate() noexcept;

	void deallocate() noexcept;

public:

	/*
	* block the thread
	* unsignaled -> signaled
	*/
	void wait(bool wait_all, uint64 timeout) noexcept;

	/*
	* non-block, for epoll
	* true : signaled
	* false : unsignaled
	*/
	bool status() noexcept;

	/*
	* reset to unsignaled
	*/
	void reset() noexcept;

};


#endif
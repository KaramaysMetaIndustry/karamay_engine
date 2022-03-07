#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include "device_object.h"

class semaphore final : public device_object<VkSemaphore>
{
public:

	semaphore(device& dev);

	semaphore(const semaphore&) = delete;
	semaphore& operator=(const semaphore&) = delete;

	~semaphore() override;

public:

	bool allocate() noexcept;

	void deallocate() noexcept;

	void bind()
	{
		vkSignalSemaphore;
		VkTimelineSemaphoreSubmitInfo;
		VkSemaphoreWaitInfo _wait;
		_wait.sType;
		_wait.pSemaphores;
		_wait.semaphoreCount;

		vkWaitSemaphores;
	}

};

struct semaphore_group
{

	void wait()
	{

	}

};

#endif
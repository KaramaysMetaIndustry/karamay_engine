#ifndef SEMAPHORE_H
#define SEMAPHORE_H
#include "device_object.h"

class vk_semaphore final : public device_object<VkSemaphore>
{
public:

	vk_semaphore(vk_device& dev);

	vk_semaphore(const vk_semaphore&) = delete;
	vk_semaphore& operator=(const vk_semaphore&) = delete;

	~vk_semaphore() override;

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
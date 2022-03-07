#ifndef FENCE_H
#define FENCE_H
#include "device_object.h"

class fence final : public device_object<VkFence>
{
public:

	bool allocate() noexcept;

	void deallocate() noexcept;

public:

	void wait(bool wait_all, uint64 timeout);

	void reset();

};


#endif
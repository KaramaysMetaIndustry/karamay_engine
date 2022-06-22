#ifndef EVENT_H
#define EVENT_H
#include "device_object.h"

class vk_event final : public device_object<VkEvent>
{
public:
	vk_event(vk_device& dev);

	vk_event(const vk_event&) = delete;
	vk_event& operator=(const vk_event&) = delete;
	
	~vk_event() override;

public:

	bool allocate() noexcept;

	void set() noexcept;

	void reset() noexcept;

	bool get_status() noexcept;

	void bind()
	{
		//vkCmdSetEvent();
	}

private:

	void _deallocate() noexcept;

};

#endif
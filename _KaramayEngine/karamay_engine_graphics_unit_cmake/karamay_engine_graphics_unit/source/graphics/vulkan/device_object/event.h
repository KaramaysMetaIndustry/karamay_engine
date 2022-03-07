#ifndef EVENT_H
#define EVENT_H
#include "device_object.h"

class event final : public device_object<VkEvent>
{
public:
	event(device& dev);

	event(const event&) = delete;
	event& operator=(const event&) = delete;
	
	~event() override {}

public:




};

#endif
#ifndef _EVENT_H_
#define _EVENT_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class Event final : public DeviceObject<VkEvent>
{
public:

	Event();

	virtual ~Event();


	bool Allocate()
	{
		VkEventCreateInfo _CreateInfo;

		if (vkCreateEvent(nullptr, &_CreateInfo, nullptr, &_Handle))
		{
			return true;
		}

		return false;
	}

	void Deallocate()
	{
		if (_Handle)
		{
			vkDestroyEvent(nullptr, _Handle, nullptr);
			_Handle = nullptr;
		}
	}


	void Set()
	{
		vkSetEvent(nullptr, Handle());
	}

	void Reset()
	{
		vkResetEvent(nullptr, Handle());
	}

	void GetStatus()
	{
		const VkResult Status = vkGetEventStatus(nullptr, Handle());
	}
	

};

_KANAS_CORE_END

#endif
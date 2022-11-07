#ifndef _FRAMEBUFFER_H_
#define _FRAMEBUFFER_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class Framebuffer final : public DeviceObject<VkFramebuffer>
{
public:

	Framebuffer(Device& InDevice);

	virtual ~Framebuffer();

};

_KANAS_CORE_END

#endif
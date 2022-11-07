#ifndef _SAMPLER_H_
#define _SAMPLER_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class Sampler final : public DeviceObject<VkSampler>
{
public:

	Sampler(Device& InDevice);

	virtual ~Sampler() override;

	bool Allocate();

};

_KANAS_CORE_END

#endif

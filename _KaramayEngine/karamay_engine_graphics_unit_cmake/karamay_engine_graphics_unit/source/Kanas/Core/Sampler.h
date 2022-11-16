#ifndef _SAMPLER_H_
#define _SAMPLER_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FSampler final : public FDeviceObject<VkSampler>
{
	friend class FDevice;

	bool Allocate();

public:

	FSampler(FDevice& InDevice);

	virtual ~FSampler() override;

};

_KANAS_CORE_END

#endif

#ifndef _SAMPLER_H_
#define _SAMPLER_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class sampler final : public deviceObject<VkSampler>
{
	friend class device;

	bool alllocate();

public:

	sampler(device& owner);

	virtual ~sampler() override;

};

_KANAS_CORE_END

#endif

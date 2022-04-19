#ifndef SAMPLER_H
#define SAMPLER_H
#include "device_object.h"

class sampler final : public device_object<VkSampler>
{
public:

	sampler(device& dev);

	sampler(const sampler&) = delete;
	sampler& operator=(const sampler&) = delete;

	~sampler() override;

};

#endif
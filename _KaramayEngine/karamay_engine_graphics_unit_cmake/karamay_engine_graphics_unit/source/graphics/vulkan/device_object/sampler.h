#ifndef SAMPLER_H
#define SAMPLER_H
#include "device_object.h"

class vk_sampler final : public device_object<VkSampler>
{
public:

	vk_sampler(vk_device& dev);

	vk_sampler(const vk_sampler&) = delete;
	vk_sampler& operator=(const vk_sampler&) = delete;

	~vk_sampler() override;

	bool allocate();

};

#endif
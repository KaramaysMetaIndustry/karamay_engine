#ifndef SAMPLER_H
#define SAMPLER_H
#include "device_object.h"

class vk_sampler final : public device_object<VkSampler>
{
	void _deallocate();

public:

	vk_sampler(vk_device& dev) : 
		device_object(dev)
	{}

	vk_sampler(const vk_sampler&) = delete;
	vk_sampler& operator=(const vk_sampler&) = delete;

	~vk_sampler() override
	{
		_deallocate();
	}

	bool allocate(const vk_sampler_parameters& parameters);

};

#endif
#ifndef SAMPLER_YCBCR_CONVERSION_H
#define SAMPLER_YCBCR_CONVERSION_H
#include "device_object.h"

class sampler_ycbcr_converion final : public device_object<VkSamplerYcbcrConversion>
{
public:

	sampler_ycbcr_converion(device& dev);

	sampler_ycbcr_converion(const sampler_ycbcr_converion&) = delete;
	sampler_ycbcr_converion& operator=(const sampler_ycbcr_converion&) = delete;

	~sampler_ycbcr_converion() override;

public:

	bool allocate() noexcept;

	void deallocate() noexcept;

};


#endif

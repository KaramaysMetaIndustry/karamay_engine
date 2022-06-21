#include "sampler_ycbcr_conversion.h"

sampler_ycbcr_converion::sampler_ycbcr_converion(device& dev) : device_object(dev)
{
}

sampler_ycbcr_converion::~sampler_ycbcr_converion()
{
	deallocate();
}

bool sampler_ycbcr_converion::allocate() noexcept
{
	VkSamplerYcbcrConversionCreateInfo _create_info;
	_create_info.sType;

	vkCreateSamplerYcbcrConversion(_dev.handle(), &_create_info, nullptr, &_handle);

	return true;
}

void sampler_ycbcr_converion::deallocate() noexcept
{
	if (_handle)
	{
		vkDestroySamplerYcbcrConversion(_dev.handle(), _handle, nullptr);
		_handle = nullptr;
	}
}

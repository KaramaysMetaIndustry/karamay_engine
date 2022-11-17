#include "Sampler.h"
#include "Device.h"

bool Kanas::Core::FSampler::Allocate()
{
	VkSamplerCreateInfo SamplerCreateInfo{};
	SamplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	SamplerCreateInfo.pNext = nullptr;
	SamplerCreateInfo.flags = {};
	SamplerCreateInfo.magFilter = VK_FILTER_LINEAR;
	SamplerCreateInfo.minFilter = VK_FILTER_CUBIC_IMG;
	SamplerCreateInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	SamplerCreateInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	SamplerCreateInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	SamplerCreateInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	SamplerCreateInfo.mipLodBias = 0.f;
	SamplerCreateInfo.anisotropyEnable = false;
	SamplerCreateInfo.maxAnisotropy = 0.f;
	SamplerCreateInfo.compareEnable = false;
	SamplerCreateInfo.compareOp = VK_COMPARE_OP_ALWAYS;
	SamplerCreateInfo.minLod = 0.f;
	SamplerCreateInfo.maxLod = 1.f;
	SamplerCreateInfo.borderColor = VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;
	SamplerCreateInfo.unnormalizedCoordinates = false;

	const VkResult SamplerCreationResult = vkCreateSampler(GetDevice().GetHandle(), &SamplerCreateInfo, nullptr, &_Handle);

	if (SamplerCreationResult == VK_SUCCESS)
	{
		return true;
	}

	return false;
}

Kanas::Core::FSampler::FSampler(FDevice& InDevice) :
	FDeviceObject(InDevice)
{
}

Kanas::Core::FSampler::~FSampler()
{
	if (IsValid())
	{
		vkDestroySampler(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}



#include "Sampler.h"
#include "Device.h"

bool Kanas::Core::FSampler::Allocate()
{
	VkSamplerCreateInfo SamplerCreateInfo{};
	SamplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	SamplerCreateInfo.pNext = nullptr;
	SamplerCreateInfo.flags = {};
	SamplerCreateInfo.magFilter = VkFilter::VK_FILTER_LINEAR;
	SamplerCreateInfo.minFilter = VkFilter::VK_FILTER_CUBIC_IMG;
	SamplerCreateInfo.mipmapMode = VkSamplerMipmapMode::VK_SAMPLER_MIPMAP_MODE_LINEAR;
	SamplerCreateInfo.addressModeU = VkSamplerAddressMode::VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	SamplerCreateInfo.addressModeV = VkSamplerAddressMode::VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	SamplerCreateInfo.addressModeW = VkSamplerAddressMode::VK_SAMPLER_ADDRESS_MODE_CLAMP_TO_BORDER;
	SamplerCreateInfo.mipLodBias = 0.f;
	SamplerCreateInfo.anisotropyEnable = false;
	SamplerCreateInfo.maxAnisotropy = 0.f;
	SamplerCreateInfo.compareEnable = false;
	SamplerCreateInfo.compareOp = VkCompareOp::VK_COMPARE_OP_ALWAYS;
	SamplerCreateInfo.minLod = 0.f;
	SamplerCreateInfo.maxLod = 1.f;
	SamplerCreateInfo.borderColor = VkBorderColor::VK_BORDER_COLOR_FLOAT_OPAQUE_BLACK;
	SamplerCreateInfo.unnormalizedCoordinates = false;

	VkResult Result = vkCreateSampler(GetDevice().GetHandle(), &SamplerCreateInfo, nullptr, &_Handle);

	if (Result == VkResult::VK_SUCCESS)
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



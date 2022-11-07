#ifndef _VULKAN_INSTANCE_H_
#define _VULKAN_INSTANCE_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class PhysicalDevice;

class VulkanInstance final : public VulkanObject<VkInstance>
{
public:

	VulkanInstance()
	{}

	virtual ~VulkanInstance() override
	{
		if (IsValid())
		{
			vkDestroyInstance(GetHandle(), nullptr);

			ResetHandle();
		}
	}

	bool Initialize()
	{
		return true;
	}

	void GetGPUs(std::vector<PhysicalDevice*>& OutGPUs) const
	{
		OutGPUs.reserve(GPUs);
		for (const auto& GPU : GPUs)
		{
			if (GPU)
			{
				OutGPUs.emplace_back(GPU.get());
			}
		}
	}

private:

	std::vector<std::unique_ptr<PhysicalDevice>> GPUs;

};

_KANAS_CORE_END

#endif
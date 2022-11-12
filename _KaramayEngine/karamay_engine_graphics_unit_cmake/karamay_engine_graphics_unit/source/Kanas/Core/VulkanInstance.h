#ifndef _VULKAN_INSTANCE_H_
#define _VULKAN_INSTANCE_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class PhysicalDevice;
class Device;

class VulkanInstance final : public VulkanObject<VkInstance>
{
public:

	VulkanInstance();

	virtual ~VulkanInstance() override;

	bool Initialize();

	void GetGPUs(TVector<PhysicalDevice*>& OutGPUs) const;

private:

	TVector<TUniquePtr<PhysicalDevice>> GPUs;

};

_KANAS_CORE_END

#endif
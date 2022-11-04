#ifndef _VULKAN_INSTANCE_H_
#define _VULKAN_INSTANCE_H_

#include "VulkanObject.h"

_KANAS_CORE_BEGIN

class VulkanInstance final : public VulkanObject<VkInstance>
{
public:

	VulkanInstance() = default;

	virtual ~VulkanInstance()
	{
		vkDestroyInstance(Handle(), nullptr);
	}

};

_KANAS_CORE_END

#endif
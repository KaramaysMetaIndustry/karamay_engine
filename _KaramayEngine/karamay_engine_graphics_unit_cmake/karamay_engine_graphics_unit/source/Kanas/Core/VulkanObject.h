#ifndef _VULKAN_OBJECT_H_
#define _VULKAN_OBJECT_H_

#include "KanasCore.h"

_KANAS_CORE_BEGIN

template<typename VkHandleT>
class VulkanObject
{
public:
	VulkanObject() = default;

	virtual ~VulkanObject() {}

protected:

	VKHandleT _Handle{ VK_NULL_HANDLE };

public:

	VkHandleT Handle() const { return _Handle; }

protected:

	void ResetHandle() { _Handle = VK_NULL_HANDLE; }

};

_KANAS_CORE_END

#endif
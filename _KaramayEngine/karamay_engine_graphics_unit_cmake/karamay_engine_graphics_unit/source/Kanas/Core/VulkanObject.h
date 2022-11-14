#ifndef _VULKAN_OBJECT_H_
#define _VULKAN_OBJECT_H_

#include "KanasCoreTypes.h"

_KANAS_CORE_BEGIN

template<typename VkHandleT>
class VulkanObject
{
public:
	VulkanObject() = default;

	virtual ~VulkanObject() {}

protected:

	VkHandleT _Handle{ VK_NULL_HANDLE };

	inline void ResetHandle() { _Handle = VK_NULL_HANDLE; }

	bool IsValid() const { return _Handle != VK_NULL_HANDLE; }

public:

	VkHandleT GetHandle() const { return _Handle; }

};

_KANAS_CORE_END

#endif
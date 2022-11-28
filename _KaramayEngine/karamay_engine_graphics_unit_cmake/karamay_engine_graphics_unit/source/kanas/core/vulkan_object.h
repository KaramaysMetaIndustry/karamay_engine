#ifndef _VULKAN_OBJECT_H_
#define _VULKAN_OBJECT_H_

#include "KanasCoreTypes.h"

_KANAS_CORE_BEGIN

template<typename VkHandleT>
class vulkan_object
{
public:
	vulkan_object() = default;

	virtual ~vulkan_object() {}

protected:

	VkHandleT handle{ VK_NULL_HANDLE };

	inline void reset_handle() { handle = VK_NULL_HANDLE; }

	bool IsValid() const { return handle != VK_NULL_HANDLE; }

public:

	VkHandleT get_handle() const { return handle; }

};

_KANAS_CORE_END

#endif
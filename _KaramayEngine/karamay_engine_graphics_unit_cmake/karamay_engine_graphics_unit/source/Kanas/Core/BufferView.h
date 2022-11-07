#ifndef _BUFFER_VIEW_H_
#define _BUFFER_VIEW_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class Buffer;

class BufferView final : public DeviceObject<VkBufferView>
{
public:

	BufferView(Device& InDevice);

	virtual ~BufferView();

	bool Allocate(Buffer* InBuffer, VkFormat InFormat, VkDeviceSize InOffset, VkDeviceSize InRange);

private:

	Buffer* Target{ nullptr };\


};

_KANAS_CORE_END

#endif
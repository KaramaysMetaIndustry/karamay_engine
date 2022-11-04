#ifndef _BUFFER_VIEW_H_
#define _BUFFER_VIEW_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class BufferView final : public DeviceObject<VkBufferView>
{
public:

	BufferView();

	virtual ~BufferView();

public:


};

_KANAS_CORE_END

#endif
#ifndef _BUFFER_VIEW_H_
#define _BUFFER_VIEW_H_

#include "DeviceObject.h"

_KANAS_CORE_BEGIN

class FBuffer;

class FBufferView final : public FDeviceObject<VkBufferView>
{
	friend class FDevice;

	bool Allocate(TSharedPtr<FBuffer> InBuffer, VkFormat InFormat, VkDeviceSize InOffset, VkDeviceSize InRange);

public:

	FBufferView(FDevice& InDevice);

	FBufferView(const FBufferView&) = delete;
	FBufferView(FBufferView&& Other);

	FBufferView& operator=(const FBufferView&) = delete;

	virtual ~FBufferView() override;

private:

	TSharedPtr<FBuffer> Buffer{};

};

_KANAS_CORE_END

#endif
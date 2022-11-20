#ifndef _BUFFER_VIEW_H_
#define _BUFFER_VIEW_H_

#include "device_object.h"

_KANAS_CORE_BEGIN

class buffer;

class buffer_view final : public device_object<VkBufferView>
{
	friend class device;

	bool alllocate(std::shared_ptr<buffer> InBuffer, VkFormat InFormat, VkDeviceSize InOffset, VkDeviceSize InRange);

public:

	buffer_view(device& owner);

	buffer_view(const buffer_view&) = delete;
	buffer_view(buffer_view&& Other);

	buffer_view& operator=(const buffer_view&) = delete;

	virtual ~buffer_view() override;

private:

	std::shared_ptr<buffer> buf{};

};

_KANAS_CORE_END

#endif
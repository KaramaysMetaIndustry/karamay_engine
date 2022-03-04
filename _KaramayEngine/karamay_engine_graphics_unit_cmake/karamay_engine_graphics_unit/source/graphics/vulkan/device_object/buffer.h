#ifndef BUFFER_H
#define BUFFER_H
#include "device_object.h"

class image;
class command_buffer;

class buffer final : public device_object<VkBuffer>
{
public:

	buffer(device& dev);

	buffer(const buffer&) = delete;
	buffer& operator=(const buffer&) = delete;

	~buffer() override;

public:

	bool allocate(uint64 size, VkBufferUsageFlagBits usage_flags, VkSharingMode sharing_mode);

	void deallocate();

public:

	void copy_to(command_buffer* recorder, buffer* dst, const std::vector<VkBufferCopy>& regions);

	void copy_to(command_buffer* recorder, image* dst);

	void fill(command_buffer* recorder, uint64 offset, uint64 size, uint32 data);

	void update(command_buffer* recorder, uint64 offset, uint64 size, void* data);

};

#endif
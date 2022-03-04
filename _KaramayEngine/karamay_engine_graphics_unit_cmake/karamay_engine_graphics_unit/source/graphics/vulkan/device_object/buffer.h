#ifndef BUFFER_H
#define BUFFER_H
#include "device_object.h"

class command_buffer;  
class image;

class buffer final : public device_object<VkBuffer>
{
public:

	buffer(device& dev);

	bool allocate(uint64 size, VkBufferUsageFlagBits usage_flags, VkSharingMode sharing_mode);

	void deallocate();

public:

	void copy_to(command_buffer* recorder, buffer* dst, const std::vector<VkBufferCopy>& regions);

	void copy_to(command_buffer* recorder, image* dst);

};

#endif
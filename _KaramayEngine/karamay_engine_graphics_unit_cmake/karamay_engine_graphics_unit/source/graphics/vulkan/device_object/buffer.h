#ifndef BUFFER_H
#define BUFFER_H
#include "device_object.h"

class device_memory;
class image;
class command_buffer;

class buffer final : public device_object<VkBuffer>
{
public:

	buffer(device& dev);

	buffer(const buffer&) = delete;
	buffer& operator=(const buffer&) = delete;

	~buffer() override;

private:

	std::shared_ptr<device_memory> _memory;

	VkBufferUsageFlags _usage_flags;

	VkSharingMode _sharing_mode;

public:

	bool allocate(uint64 size, VkBufferUsageFlags usage_flags, VkSharingMode sharing_mode) noexcept;

	void deallocate() noexcept;

public:

	std::shared_ptr<const device_memory> memory() const noexcept { return _memory; }

	VkBufferUsageFlags usage() const noexcept { return _usage_flags; }

	VkSharingMode sharing_mode() const noexcept { return _sharing_mode; }

public:

	/*
	* gpu all controlled
	*/
	void copy_to(command_buffer* recorder, buffer* dst, const std::vector<VkBufferCopy>& regions);

	/*
	* gpu all controlled
	*/
	void copy_to(command_buffer* recorder, image* dst, const std::vector<VkBufferImageCopy>& regions);

	/*
	* gpu mostly all controlled
	*/
	void fill(command_buffer* recorder, uint64 offset, uint64 size, uint32 data);

	/*
	* gpu all controlled
	*/
	void update(command_buffer* recorder, uint64 offset, uint64 size, void* data);

};

#endif
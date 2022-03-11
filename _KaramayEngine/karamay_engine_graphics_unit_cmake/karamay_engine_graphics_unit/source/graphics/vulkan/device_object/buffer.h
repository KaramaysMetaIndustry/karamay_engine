#ifndef BUFFER_H
#define BUFFER_H
#include "device_object.h"
#include "device_memory.h"

class device_memory;
class image;
class command_buffer;

class buffer final : public device_object<VkBuffer> 
{
public:
	explicit buffer(device& dev, uint64 size, VkBufferUsageFlags usage, VkSharingMode sharing);
	

	buffer(const buffer&) = delete;
	buffer& operator=(const buffer&) = delete;

	~buffer() override;

public:

	uint64 size() const { _Memory->size(); }

	device_memory& memory() noexcept { return *_Memory; }

	const device_memory& memory() const noexcept { return *_Memory; }

public:

	/*
	* gpu all controlled
	*/
	void copy_to(command_buffer* recorder, buffer& dst, const std::vector<VkBufferCopy>& regions);

	/*
	* gpu all controlled
	*/
	void copy_to(command_buffer* recorder, image& dst, const std::vector<VkBufferImageCopy>& regions);

	/*
	* gpu mostly all controlled
	*/
	void fill(command_buffer* recorder, uint64 offset, uint64 size, uint32 data);

	/*
	* gpu all controlled
	*/
	void update(command_buffer* recorder, uint64 offset, uint64 size, void* data);

private:

	void _Deallocate() noexcept;

	std::unique_ptr<device_memory> _Memory;

};

class buffer_view final : public device_object<VkBufferView>
{
public:

	explicit buffer_view(device& dev, buffer& buf, VkFormat format) noexcept;
	
	explicit buffer_view(device& dev, buffer& buf, VkFormat format, uint32 offset, uint32 size) noexcept;
	
	buffer_view(const buffer_view&) = delete;
	buffer_view& operator=(const buffer_view&) = delete;

	~buffer_view() noexcept override;

private:

	void _Construct_nothrow(buffer& buf, VkFormat format, uint32 offset, uint32 size) noexcept;

	void _Destroy() noexcept;

private:

	buffer& _Target;

	VkFormat _Format;

	uint64 _Offset = 0;

	uint64 _Size = 0;

};

#endif
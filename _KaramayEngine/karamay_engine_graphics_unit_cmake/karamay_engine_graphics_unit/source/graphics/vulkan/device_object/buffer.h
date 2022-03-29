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

	buffer(buffer&& rhs) noexcept
		: device_object(rhs._dev), _memory(std::move(rhs._memory))
	{}

	buffer& operator=(const buffer&) = delete;

	~buffer() noexcept override;

public:

	uint64 size() const noexcept { _memory->size(); }

	device_memory& memory() noexcept { return *_memory; }

	const device_memory& memory() const noexcept { return *_memory; }

public:

	/*
	* gpu all controlled
	*/
	void copy_to(command_buffer& recorder, buffer& dst, const std::vector<VkBufferCopy>& regions);

	/*
	* gpu all controlled
	*/
	void copy_to(command_buffer& recorder, image& dst, const std::vector<VkBufferImageCopy>& regions);

	/*
	* gpu mostly all controlled
	*/
	void fill(command_buffer& recorder, uint64 offset, uint64 size, uint32 data);

	/*
	* gpu all controlled
	*/
	void update(command_buffer& recorder, uint64 offset, uint64 size, void* data);

private:

	std::unique_ptr<device_memory> _memory;

};

class buffer_view final : public device_object<VkBufferView>
{
public:

	explicit buffer_view(device& dev, buffer& buf, VkFormat format) noexcept;
	
	explicit buffer_view(device& dev, buffer& buf, VkFormat format, uint32 offset, uint32 size) noexcept;
	
	buffer_view(const buffer_view&) = delete;
	buffer_view& operator=(const buffer_view&) = delete;

	buffer_view(buffer_view&& rhs) noexcept
		: device_object(rhs._dev), _target(rhs._target)
	{

	}

	~buffer_view() noexcept override;

private:

	void _Construct_nothrow(buffer& buf, VkFormat format, uint32 offset, uint32 size) noexcept;

private:

	buffer& _target;

	VkFormat _format;

	uint64 _offset = 0;

	uint64 _size = 0;

};

#endif
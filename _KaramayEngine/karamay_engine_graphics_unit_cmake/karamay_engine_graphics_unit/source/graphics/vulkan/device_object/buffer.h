#ifndef BUFFER_H
#define BUFFER_H
#include "device_object.h"
#include "device_memory.h"

class vk_device_memory;
class image;
class command_buffer;

class vk_buffer final : public device_object<VkBuffer> 
{

	std::unique_ptr<vk_device_memory> _memory;

public:

	explicit vk_buffer(device& dev);

	vk_buffer(const vk_buffer&) = delete;

	vk_buffer(vk_buffer&& rhs) noexcept
		: device_object(rhs._dev), _memory(std::move(rhs._memory))
	{}

	vk_buffer& operator=(const vk_buffer&) = delete;

	~vk_buffer() override;

public:

	bool allocate(uint64 size, VkBufferUsageFlags usage, VkSharingMode sharing);

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


};

class vk_buffer_view final : public device_object<VkBufferView>
{
public:

	explicit vk_buffer_view(device& dev) noexcept;
	
	vk_buffer_view(const vk_buffer_view&) = delete;
	vk_buffer_view& operator=(const vk_buffer_view&) = delete;

	vk_buffer_view(vk_buffer_view&& rhs) noexcept
		: device_object(rhs._dev), _target(rhs._target)
	{
	}

	~vk_buffer_view() override;

public:

	bool allocate(std::shared_ptr<vk_buffer> buf, VkFormat format, uint32 offset, uint32 size);

private:

	std::shared_ptr<vk_buffer> _target;

	VkFormat _format;

	uint64 _offset = 0;

	uint64 _size = 0;

};

#endif
#ifndef BUFFER_H
#define BUFFER_H
#include "device_object.h"
#include "device_memory.h"

class vk_device_memory;
class vk_image;
class vk_command_buffer;

class vk_buffer final : public device_object<VkBuffer> 
{

	std::shared_ptr<vk_device_memory> _memory;

public:

	explicit vk_buffer(vk_device& dev);

	vk_buffer(const vk_buffer&) = delete;

	vk_buffer(vk_buffer&& rhs) noexcept
		: device_object(rhs._dev), _memory(std::move(rhs._memory))
	{}

	vk_buffer& operator=(const vk_buffer&) = delete;

	~vk_buffer() override;

public:

	bool allocate(const vk_buffer_parameters& parameters);

public:

	/*
	* gpu all controlled
	*/
	void copy_to(vk_command_buffer& recorder, vk_buffer& dst, const std::vector<VkBufferCopy>& regions);

	/*
	* gpu all controlled
	*/
	void copy_to(vk_command_buffer& recorder, vk_image& dst, const std::vector<VkBufferImageCopy>& regions);

	/*
	* gpu mostly all controlled
	*/
	void fill(vk_command_buffer& recorder, uint64 offset, uint64 size, uint32 data);

	/*
	* gpu all controlled
	*/
	void update(vk_command_buffer& recorder, uint64 offset, uint64 size, void* data);


};

class vk_buffer_view final : public device_object<VkBufferView>
{

	vk_buffer& _target;

	VkFormat _format;

	uint64 _offset = 0;

	uint64 _size = 0;

public:

	explicit vk_buffer_view(vk_device& dev, vk_buffer& buffer) noexcept;
	
	vk_buffer_view(const vk_buffer_view&) = delete;
	vk_buffer_view& operator=(const vk_buffer_view&) = delete;

	vk_buffer_view(vk_buffer_view&& rhs) noexcept
		: device_object(rhs._dev), _target(rhs._target)
	{
	}

	~vk_buffer_view() override;

public:

	bool allocate(const vk_buffer_view_parameters& parameters);

};

#endif
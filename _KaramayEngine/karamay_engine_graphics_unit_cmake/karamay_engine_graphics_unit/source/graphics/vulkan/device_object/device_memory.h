#ifndef DEVICE_MEMORY_H
#define DEVICE_MEMORY_H
#include "device_object.h"

class vk_device_memory final : public device_object<VkDeviceMemory>
{
	uint64 _size = 0;

	uint32 _find_memory_type(uint32 typeFilter, VkMemoryPropertyFlags properties) noexcept;

	void _deallocate() noexcept;

public:

	explicit vk_device_memory(vk_device& dev)
		: device_object(dev)
	{}

	vk_device_memory(const vk_device_memory&) = delete;
	vk_device_memory& operator=(const vk_device_memory&) = delete;

	~vk_device_memory() override
	{
		_deallocate();
	}

	bool allocate(const vk_device_memory_parameters& parameters);
	

	using device_memory_handler = std::function<void(uint64 size, void* data)>;
	
	void exec_handler(uint64 offset, uint64 size, const device_memory_handler& handler, VkMemoryMapFlags flags = {}) const noexcept;

	void exec_handler(const device_memory_handler& handler, VkMemoryMapFlags flags = {}) noexcept; 


	uint64 size() const { return _size; }

};

#endif
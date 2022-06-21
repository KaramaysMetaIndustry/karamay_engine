#ifndef DEVICE_MEMORY_H
#define DEVICE_MEMORY_H
#include "device_object.h"

class vk_device_memory final : public device_object<VkDeviceMemory>
{
public:

	explicit vk_device_memory(device& dev, const VkMemoryRequirements& requirements) noexcept
		: device_object(dev), _size(requirements.size)
	{
		VkMemoryAllocateInfo _Alloc_info
		{
			.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
			.allocationSize = requirements.size,
			.memoryTypeIndex = _find_memory_type(
				requirements.memoryTypeBits,
				VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT
			)
		};

		VkResult _result = vkAllocateMemory(_dev.handle(), &_Alloc_info, nullptr, &_handle);
	}

	explicit vk_device_memory(device& dev, uint64 size, uint32 memory_type_index) noexcept
		:device_object(dev), _size(size)
	{
		VkMemoryAllocateInfo _Alloc_info
		{
			.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
			.pNext = nullptr,
			.allocationSize = size,
			.memoryTypeIndex = memory_type_index
		};

		VkResult _Result = vkAllocateMemory(_dev.handle(), &_Alloc_info, nullptr, &_handle);
	}

	vk_device_memory(const vk_device_memory&) = delete;
	vk_device_memory& operator=(const vk_device_memory&) = delete;

	~vk_device_memory() noexcept override;

public:
	
	using device_memory_handler = std::function<void(uint64 size, void* data)>;
	
	/*
	* cpu ~ gpu
	* this action will cost bandwidth, and this should be called in main thread
	* [](uint64 size, void* data) {}
	*/
	void exec_handler(uint64 offset, uint64 size, const device_memory_handler& handler, VkMemoryMapFlags flags = {}) const noexcept;

	/*
	* 
	* [](uint64 size, void* data) {}
	*/
	void exec_handler(const device_memory_handler& handler, VkMemoryMapFlags flags = {}) noexcept; 

public:

	uint64 size() const { return _size; }

private:

	uint32 _find_memory_type(uint32 typeFilter, VkMemoryPropertyFlags properties) noexcept;

	void _deallocate() noexcept;

	uint64 _size = 0;
	
};

#endif
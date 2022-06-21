#include "descriptor_pool.h"
#include "descriptor_set_layout.h"
#include "pooled_object/descriptor_set.h"

vk_descriptor_pool::vk_descriptor_pool(vk_device& dev, uint32 count, uint32 max, const VkDescriptorPoolSize& pool_size) : device_object(dev)
{
	
}

vk_descriptor_pool::~vk_descriptor_pool()
{
	vkDestroyDescriptorPool(_dev.handle(), _handle, nullptr);
}

bool vk_descriptor_pool::allocate(uint32 count, uint32 max, const VkDescriptorPoolSize& pool_size)
{
	VkDescriptorPoolCreateInfo _create_info
	{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.flags = 0,
		.maxSets = max,
		.poolSizeCount = count,
		.pPoolSizes = &pool_size,
	};

	if (vkCreateDescriptorPool(_dev.handle(), &_create_info, nullptr, &_handle) == VkResult::VK_SUCCESS)
	{
		return true;
	}

	return false;
}

void vk_descriptor_pool::reset(VkDescriptorPoolResetFlags flags) noexcept
{
	vkResetDescriptorPool(_dev.handle(), _handle, flags);
}

std::shared_ptr<vk_descriptor_set> vk_descriptor_pool::create_descriptor_set(const vk_descriptor_set_layout& layout) noexcept
{
	return std::make_shared<vk_descriptor_set>(_dev, *this, layout);
}

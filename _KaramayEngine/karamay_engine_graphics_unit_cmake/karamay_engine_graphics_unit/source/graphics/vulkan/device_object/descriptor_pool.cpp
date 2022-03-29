#include "descriptor_pool.h"
#include "descriptor_set_layout.h"
#include "pooled_object/descriptor_set.h"

descriptor_pool::descriptor_pool(device& dev, uint32 count, uint32 max, const VkDescriptorPoolSize& pool_size) : device_object(dev)
{
	VkDescriptorPoolCreateInfo _create_info
	{
		.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO,
		.flags = 0,
		.maxSets = max,
		.poolSizeCount = count,
		.pPoolSizes = &pool_size,
	};

	auto _result = vkCreateDescriptorPool(_dev.handle(), &_create_info, nullptr, &_handle);
}

descriptor_pool::~descriptor_pool()
{
	vkDestroyDescriptorPool(_dev.handle(), _handle, nullptr);
}

void descriptor_pool::reset(VkDescriptorPoolResetFlags flags) noexcept
{
	vkResetDescriptorPool(_dev.handle(), _handle, flags);
}

std::shared_ptr<descriptor_set> descriptor_pool::create_descriptor_set(const descriptor_set_layout& layout) noexcept
{
	return std::make_shared<descriptor_set>(_dev, *this, layout);
}

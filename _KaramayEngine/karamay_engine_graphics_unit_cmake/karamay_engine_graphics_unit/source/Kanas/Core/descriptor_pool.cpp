#include "descriptor_pool.h"
#include "descriptor_set.h"
#include "device.h"

bool kanas::core::descriptor_pool::alllocate(const std::vector<VkDescriptorPoolSize>& InPoolSizes, std::uint32_t MaxSets)
{
	VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo{};
	DescriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	DescriptorPoolCreateInfo.pNext = nullptr;
	DescriptorPoolCreateInfo.flags = {};
	DescriptorPoolCreateInfo.pPoolSizes = InPoolSizes.data();
	DescriptorPoolCreateInfo.poolSizeCount = static_cast<std::uint32_t>(InPoolSizes.size());
	DescriptorPoolCreateInfo.maxSets = MaxSets;

	const VkResult Result = vkCreateDescriptorPool(get_device().get_handle(), &DescriptorPoolCreateInfo, nullptr, &handle);

	if (Result == VK_SUCCESS)
	{
		return true;
	}

	return false;
}

kanas::core::descriptor_pool::descriptor_pool(device& owner) :
	device_object(owner)
{
}

kanas::core::descriptor_pool::~descriptor_pool()
{
	if (IsValid())
	{
		vkDestroyDescriptorPool(get_device().get_handle(), get_handle(), nullptr);

		reset_handle();
	}
}



kanas::core::descriptor_set* kanas::core::descriptor_pool::CreateDescriptorSet(descriptor_set_layout& InSetLayout)
{
	const auto NewDescriptorSet = std::make_unique<descriptor_set>(get_device(), *this);
	
	if (NewDescriptorSet && NewDescriptorSet->alllocate(InSetLayout))
	{
		DescriptorSets.push_back(NewDescriptorSet);
		return NewDescriptorSet.get();
	}

	return nullptr;
}

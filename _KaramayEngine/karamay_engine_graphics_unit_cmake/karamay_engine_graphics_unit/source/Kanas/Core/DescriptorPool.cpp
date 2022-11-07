#include "DescriptorPool.h"
#include "DescriptorSet.h"
#include "Device.h"

Kanas::Core::DescriptorPool::DescriptorPool(Device& InDevice) :
	DeviceObject(InDevice)
{
}

Kanas::Core::DescriptorPool::~DescriptorPool()
{
	if (IsValid())
	{
		vkDestroyDescriptorPool(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}

bool Kanas::Core::DescriptorPool::Allocate()
{
	VkDescriptorPoolSize DescriptorPoolSize;
	DescriptorPoolSize.type;
	DescriptorPoolSize.descriptorCount;

	VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo;
	DescriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	DescriptorPoolCreateInfo.pNext = nullptr;
	DescriptorPoolCreateInfo.flags = {};
	DescriptorPoolCreateInfo.pPoolSizes = &DescriptorPoolSize;
	DescriptorPoolCreateInfo.poolSizeCount = 1;
	DescriptorPoolCreateInfo.maxSets;

	VkResult Result = vkCreateDescriptorPool(GetDevice().GetHandle(), &DescriptorPoolCreateInfo, nullptr, &_Handle);
	
	if (Result == VkResult::VK_SUCCESS)
	{
		return true;
	}
	
	return false;
}

Kanas::Core::DescriptorSet* Kanas::Core::DescriptorPool::CreateDescriptorSet(DescriptorSetLayout& InSetLayout)
{
	const auto NewDescriptorSet = std::make_unique<DescriptorSet>(GetDevice(), *this);
	
	if (NewDescriptorSet && NewDescriptorSet->Allocate(InSetLayout))
	{
		DescriptorSets.push_back(NewDescriptorSet);
		return NewDescriptorSet.get();
	}

	return nullptr;
}

#include "DescriptorPool.h"
#include "DescriptorSet.h"
#include "Device.h"

bool Kanas::Core::FDescriptorPool::Allocate(const TVector<VkDescriptorPoolSize>& InPoolSizes, uint32 MaxSets)
{
	VkDescriptorPoolCreateInfo DescriptorPoolCreateInfo{};
	DescriptorPoolCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	DescriptorPoolCreateInfo.pNext = nullptr;
	DescriptorPoolCreateInfo.flags = {};
	DescriptorPoolCreateInfo.pPoolSizes = InPoolSizes.data();
	DescriptorPoolCreateInfo.poolSizeCount = static_cast<uint32>(InPoolSizes.size());
	DescriptorPoolCreateInfo.maxSets = MaxSets;

	const VkResult Result = vkCreateDescriptorPool(GetDevice().GetHandle(), &DescriptorPoolCreateInfo, nullptr, &_Handle);

	if (Result == VK_SUCCESS)
	{
		return true;
	}

	return false;
}

Kanas::Core::FDescriptorPool::FDescriptorPool(FDevice& InDevice) :
	FDeviceObject(InDevice)
{
}

Kanas::Core::FDescriptorPool::~FDescriptorPool()
{
	if (IsValid())
	{
		vkDestroyDescriptorPool(GetDevice().GetHandle(), GetHandle(), nullptr);

		ResetHandle();
	}
}



Kanas::Core::FDescriptorSet* Kanas::Core::FDescriptorPool::CreateDescriptorSet(FDescriptorSetLayout& InSetLayout)
{
	const auto NewDescriptorSet = std::make_unique<FDescriptorSet>(GetDevice(), *this);
	
	if (NewDescriptorSet && NewDescriptorSet->Allocate(InSetLayout))
	{
		DescriptorSets.push_back(NewDescriptorSet);
		return NewDescriptorSet.get();
	}

	return nullptr;
}

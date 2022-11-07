#include "DescriptorSet.h"
#include "DescriptorSetLayout.h"
#include "DescriptorPool.h"
#include "Device.h"

Kanas::Core::DescriptorSet::DescriptorSet(Device& InDevice, DescriptorPool& InPool) :
	DeviceObject(InDevice), Pool(InPool)
{
}

Kanas::Core::DescriptorSet::~DescriptorSet()
{
	if (IsValid())
	{
        vkFreeDescriptorSets(GetDevice().GetHandle(), Pool.GetHandle(), 1, &_Handle);

		ResetHandle();
	}
}

bool Kanas::Core::DescriptorSet::Allocate(DescriptorSetLayout& InLayout)
{
    VkDescriptorSetLayout LayoutHandles[] = { InLayout.GetHandle() };

    VkDescriptorSetAllocateInfo DescriptorSetAllocateInfo;
    DescriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    DescriptorSetAllocateInfo.descriptorPool = Pool.GetHandle();
    DescriptorSetAllocateInfo.descriptorSetCount = 1;
    DescriptorSetAllocateInfo.pSetLayouts = LayoutHandles;

    VkResult Result = vkAllocateDescriptorSets(GetDevice().GetHandle(), &DescriptorSetAllocateInfo, &_Handle);
    
    if (Result == VkResult::VK_SUCCESS)
    {
        return true;
    }
    
    return false;
}

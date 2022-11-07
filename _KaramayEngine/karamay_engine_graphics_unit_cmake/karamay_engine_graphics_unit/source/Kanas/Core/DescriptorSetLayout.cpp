#include "DescriptorSetLayout.h"
#include "Device.h"

Kanas::Core::DescriptorSetLayout::DescriptorSetLayout(Device& InDevice) :
    DeviceObject(InDevice)
{
}

Kanas::Core::DescriptorSetLayout::~DescriptorSetLayout()
{
}

bool Kanas::Core::DescriptorSetLayout::Allocate()
{
    std::vector<VkDescriptorSetLayoutBinding> VkDescriptorSetLayoutBindings;

    VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo;
    DescriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    DescriptorSetLayoutCreateInfo.pNext = nullptr;
    DescriptorSetLayoutCreateInfo.flags;
    DescriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32>(VkDescriptorSetLayoutBindings.size());
    DescriptorSetLayoutCreateInfo.pBindings = VkDescriptorSetLayoutBindings.data();

    VkResult Result = vkCreateDescriptorSetLayout(GetDevice().Handle(), &DescriptorSetLayoutCreateInfo, nullptr, &_Handle);
    if (Result == VkResult::VK_SUCCESS)
    {
        return true;
    }
    return false;
}

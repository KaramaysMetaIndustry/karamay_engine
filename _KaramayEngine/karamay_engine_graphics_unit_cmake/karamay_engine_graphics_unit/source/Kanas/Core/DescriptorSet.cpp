#include "DescriptorSet.h"
#include "DescriptorSetLayout.h"
#include "DescriptorPool.h"
#include "DescriptorUpdateTemplate.h"
#include "Device.h"
#include "CommandBuffer.h"
#include "Pipeline.h"
#include "PipelineLayout.h"
#include "ImageView.h"
#include "Image.h"
#include "BufferView.h"
#include "Buffer.h"
#include "Sampler.h"

bool Kanas::Core::FDescriptorSet::Allocate(TSharedPtr<FDescriptorSetLayout> InLayout)
{
    VkDescriptorSetLayout LayoutHandles[] = { InLayout->GetHandle() };

    VkDescriptorSetAllocateInfo DescriptorSetAllocateInfo{};
    DescriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    DescriptorSetAllocateInfo.descriptorPool = Pool.GetHandle();
    DescriptorSetAllocateInfo.descriptorSetCount = 1;
    DescriptorSetAllocateInfo.pSetLayouts = LayoutHandles;

    const VkResult DescriptorSetsAllocationResult = vkAllocateDescriptorSets(GetDevice().GetHandle(), &DescriptorSetAllocateInfo, &_Handle);

    if (DescriptorSetsAllocationResult == VK_SUCCESS)
    {
        Layout = InLayout;

        return true;
    }

    return false;
}

void Kanas::Core::FDescriptorSet::Write(uint32 BindingIndex, uint32 ArrayIndex, const TVector<FDescriptorImageInfo>& DescriptorImageInfos)
{
    TVector<VkDescriptorImageInfo> _ImageInfos;
    for (const auto& DescriptorImageInfo : DescriptorImageInfos)
    {
        VkDescriptorImageInfo _ImageInfo;
        _ImageInfo.sampler = DescriptorImageInfo.Sampler->GetHandle();
        _ImageInfo.imageView = DescriptorImageInfo.ImageView->GetHandle();
        _ImageInfo.imageLayout = DescriptorImageInfo.ImageView->GetImage()->GetLayout();
        _ImageInfos.emplace_back(_ImageInfo);
    }

    VkWriteDescriptorSet WriteDescriptorSet{};
    WriteDescriptorSet.sType == VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    WriteDescriptorSet.pNext = nullptr;
    WriteDescriptorSet.dstSet = GetHandle();
    WriteDescriptorSet.dstBinding = BindingIndex;
    WriteDescriptorSet.dstArrayElement = ArrayIndex;
    WriteDescriptorSet.descriptorCount = static_cast<uint32>(_ImageInfos.size());
    WriteDescriptorSet.descriptorType = Layout->GetBindingInfo(BindingIndex)->descriptorType;
    WriteDescriptorSet.pImageInfo = _ImageInfos.data();
    WriteDescriptorSet.pBufferInfo = nullptr;
    WriteDescriptorSet.pTexelBufferView = nullptr;

    vkUpdateDescriptorSets(GetDevice().GetHandle(), 1, &WriteDescriptorSet, 0, nullptr);
}

void Kanas::Core::FDescriptorSet::Copy(uint32 SrcBindingIndex, uint32 SrcArrayIndex, TSharedPtr<FDescriptorSet> DstDescriptorSet, uint32 DstBindingIndex, uint32 DstArrayIndex, uint32 CopyNum)
{
    VkCopyDescriptorSet CopyDescriptorSet{};
    CopyDescriptorSet.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
    CopyDescriptorSet.pNext = nullptr;
    CopyDescriptorSet.srcSet = GetHandle();
    CopyDescriptorSet.srcBinding = SrcBindingIndex;
    CopyDescriptorSet.srcArrayElement = SrcArrayIndex;
    CopyDescriptorSet.dstSet = DstDescriptorSet->GetHandle();
    CopyDescriptorSet.dstBinding = DstBindingIndex;
    CopyDescriptorSet.dstArrayElement = DstArrayIndex;
    CopyDescriptorSet.descriptorCount = CopyNum;

    vkUpdateDescriptorSets(GetDevice().GetHandle(), 0, nullptr, 1, &CopyDescriptorSet);
}

void Kanas::Core::FDescriptorSet::Update(TSharedPtr<FDescriptorUpdateTemplate> InTemplate)
{
    vkUpdateDescriptorSetWithTemplate(GetDevice().GetHandle(), GetHandle(), InTemplate->GetHandle(), nullptr);
}

void Kanas::Core::FDescriptorSet::CmdPushDescriptorSet(FCommandBuffer& InRecorder)
{
    //vkCmdPushDescriptorSetKHR(InRecorder.GetHandle(),);
}

void Kanas::Core::FDescriptorSet::CmdPushDescriptorSetWithTemplate(FCommandBuffer& InRecorder)
{
    //vkCmdPushDescriptorSetWithTemplateKHR();
}

Kanas::Core::FDescriptorSet::FDescriptorSet(FDevice& InDevice, FDescriptorPool& InPool) :
	FDeviceObject(InDevice), Pool(InPool)
{
}

Kanas::Core::FDescriptorSet::~FDescriptorSet()
{
	if (IsValid())
	{
        vkFreeDescriptorSets(GetDevice().GetHandle(), Pool.GetHandle(), 1, &_Handle);

		ResetHandle();
	}
}

TSharedPtr<Kanas::Core::FDescriptorSetLayout> Kanas::Core::FDescriptorSet::GetLayout() const
{
    return Layout;
}



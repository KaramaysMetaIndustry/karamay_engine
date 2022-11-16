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

    const VkResult Result = vkAllocateDescriptorSets(GetDevice().GetHandle(), &DescriptorSetAllocateInfo, &_Handle);

    if (Result == VK_SUCCESS)
    {
        Layout = InLayout;
        return true;
    }

    return false;
}

TSharedPtr<Kanas::Core::FDescriptorSetLayout> Kanas::Core::FDescriptorSet::GetLayout() const
{
    return Layout;
}

void Kanas::Core::FDescriptorSet::Update()
{
    TSharedPtr<FImageView> ImageView;
    TSharedPtr<FSampler> ImageSampler;

    VkDescriptorImageInfo ImageInfo{};
    ImageInfo.imageLayout = ImageView->GetImage()->GetLayout();
    ImageInfo.imageView = ImageView->GetHandle();
    ImageInfo.sampler = ImageSampler->GetHandle();

    TSharedPtr<FBuffer> Buffer;

    VkDescriptorBufferInfo BufferInfo{};
    BufferInfo.buffer = Buffer->GetHandle();
    BufferInfo.offset;
    BufferInfo.range;

    VkWriteDescriptorSet WriteDescriptorSet{};
    WriteDescriptorSet.sType == VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
    WriteDescriptorSet.pNext = nullptr;
    WriteDescriptorSet.dstSet = GetHandle();
    WriteDescriptorSet.dstBinding = 0;
    WriteDescriptorSet.dstArrayElement = 0;
    WriteDescriptorSet.descriptorCount = 1;
    WriteDescriptorSet.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLER;
    WriteDescriptorSet.pImageInfo = nullptr;
    WriteDescriptorSet.pBufferInfo = nullptr;
    WriteDescriptorSet.pTexelBufferView = nullptr;

    VkCopyDescriptorSet CopyDescriptorSet{};
    CopyDescriptorSet.sType = VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
    CopyDescriptorSet.pNext = nullptr;
    CopyDescriptorSet.srcSet;
    CopyDescriptorSet.srcBinding;
    CopyDescriptorSet.srcArrayElement;
    CopyDescriptorSet.dstSet;
    CopyDescriptorSet.dstBinding;
    CopyDescriptorSet.dstArrayElement;
    CopyDescriptorSet.descriptorCount;

    vkUpdateDescriptorSets(GetDevice().GetHandle(), 1, &WriteDescriptorSet, 0, nullptr);
}

void Kanas::Core::FDescriptorSet::Update(TSharedPtr<FDescriptorUpdateTemplate> InTemplate)
{
    vkUpdateDescriptorSetWithTemplate(GetDevice().GetHandle(), GetHandle(), InTemplate->GetHandle(), nullptr);
}

void Kanas::Core::FDescriptorSet::CmdBind(FCommandBuffer& InRecorder, TSharedPtr<FPipeline> InPipeline)
{
    vkCmdBindDescriptorSets(InRecorder.GetHandle(), InPipeline->GetBindPoint(), InPipeline->GetLayout()->GetHandle(),)
}

void Kanas::Core::FDescriptorSet::CmdPushDescriptorSet(FCommandBuffer& InRecorder)
{
    vkCmdPushDescriptorSetKHR(InRecorder.GetHandle(),);
}

void Kanas::Core::FDescriptorSet::CmdPushDescriptorSetWithTemplate(FCommandBuffer& InRecorder)
{
    vkCmdPushDescriptorSetWithTemplateKHR();
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



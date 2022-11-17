#include "DescriptorSetLayout.h"
#include "Device.h"
#include "Sampler.h"

bool Kanas::Core::FDescriptorSetLayout::Allocate()
{
    TSharedPtr<FSampler> ImmutableSampler;

    // Sampler
    // uniform sampler
    
    // CombinedImageSampler
    // uniform sampler2D, sampler3D ...
    
    // SampledImage
    // uniform texture2D, texture3D ...
    
    // StorageImage 
    // uniform image2D, image3D ...
    
    // UniformTexelBuffer
    // uniform textureBuffer 
    
    // StorageTexelBuffer
    // uniform imageBuffer
    
    
    // UniformBuffer
    // uniform
    
    // StorageBuffer
    // buffer
    
    // UniformBufferDynamic
    // StorageBufferDynamic
    
    // InputAttachment
    // uniform subpassInput

    FShaderStageFlags StageFlags;
    StageFlags.SetAllGraphics();

    struct FDescriptorSetLayoutBinding
    {
        uint32 Count{ 0 };

        EDescriptorType Type{ EDescriptorType::SampledImage };

        FShaderStageFlags Stages{};

        TVector<TSharedPtr<FSampler>> ImmutableSamplers;
    };

    TVector<FDescriptorSetLayoutBinding> Bindings;
    TVector<VkDescriptorSetLayoutBinding> VkDescriptorSetLayoutBindings;

    for (const auto& Binding : Bindings)
    {
        FDescriptorSetLayoutBinding SetLayoutBinding
        {
            .Count = 4,
            .Type = EDescriptorType::SampledImage,
            .Stages = FShaderStageFlags().SetAllGraphics()
        };

        VkDescriptorSetLayoutBinding VkBinding;
        VkBinding.binding = 0;
        VkBinding.descriptorType = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
        VkBinding.descriptorCount = 1;
        VkBinding.stageFlags = StageFlags.Get();
        VkBinding.pImmutableSamplers;
    }
    

    VkDescriptorSetLayoutCreateInfo DescriptorSetLayoutCreateInfo{};
    DescriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    DescriptorSetLayoutCreateInfo.pNext = nullptr;
    DescriptorSetLayoutCreateInfo.flags = {};
    DescriptorSetLayoutCreateInfo.bindingCount = static_cast<uint32>(VkDescriptorSetLayoutBindings.size());
    DescriptorSetLayoutCreateInfo.pBindings = VkDescriptorSetLayoutBindings.data();

    const VkResult DescriptorSetLayoutCreationResult = vkCreateDescriptorSetLayout(GetDevice().GetHandle(), &DescriptorSetLayoutCreateInfo, nullptr, &_Handle);
    
    if (DescriptorSetLayoutCreationResult == VK_SUCCESS)
    {
        return true;
    }

    return false;
}

Kanas::Core::FDescriptorSetLayout::FDescriptorSetLayout(FDevice& InDevice) :
    FDeviceObject(InDevice)
{
}

Kanas::Core::FDescriptorSetLayout::~FDescriptorSetLayout()
{
    if (IsValid())
    {
        vkDestroyDescriptorSetLayout(GetDevice().GetHandle(), GetHandle(), nullptr);

        ResetHandle();
    }
}



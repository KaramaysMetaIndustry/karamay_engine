#include "device.h"
#include "physical_device.h"
#include "queue.h"
#include "fence.h"
#include "semaphore.h"
#include "event.h"
#include "commandBuffer.h"
#include "device_memory.h"
#include "buffer.h"
#include "buffer_view.h"
#include "image.h"
#include "image_view.h"
#include "framebuffer.h"
#include "shader_module.h"
#include "sampler.h"
#include "descriptor_pool.h"
#include "command_pool.h"
#include "render_pass.h"


bool kanas::core::device::alllocate()
{
    VkDeviceCreateFlags DeviceCreateFlags;

    std::vector<VkDeviceQueueCreateInfo> QueueCreateInfos;

    std::vector<VkQueueFamilyProperties> PropertiesArr;
    GetPhysicalDevice().GetQueueFamilyProperties(PropertiesArr);

    for (const auto& Properties : PropertiesArr)
    {
        Properties.queueCount;
        Properties.queueFlags;
        Properties.minImageTransferGranularity;
        Properties.timestampValidBits;

        const bool bIsProtectedQueue = false;
        VkDeviceQueueCreateFlags QueueCreateFlags;
        if (bIsProtectedQueue)
        {
            QueueCreateFlags |= VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT;
        }

        VkDeviceQueueCreateInfo QueueCreateInfo{};
        QueueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        QueueCreateInfo.pNext = nullptr;
        QueueCreateInfo.flags = QueueCreateFlags;
        QueueCreateInfo.queueFamilyIndex;
        QueueCreateInfo.queueCount;
        QueueCreateInfo.pQueuePriorities;

        QueueCreateInfos.emplace_back(QueueCreateInfo);
    }

    std::vector<const char*> EnabledLayerNames;
    std::vector<const char*> EnabledExtensionNames;

    VkPhysicalDeviceFeatures Features;
    GetPhysicalDevice().GetFeatures(Features);

    VkDeviceCreateInfo DeviceCreateInfo;
    DeviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    DeviceCreateInfo.pNext = nullptr;
    DeviceCreateInfo.flags = DeviceCreateFlags;
    DeviceCreateInfo.queueCreateInfoCount = static_cast<std::uint32_t>(QueueCreateInfos.size());
    DeviceCreateInfo.pQueueCreateInfos = QueueCreateInfos.data();
    DeviceCreateInfo.enabledLayerCount = static_cast<std::uint32_t>(EnabledLayerNames.size());
    DeviceCreateInfo.ppEnabledLayerNames = EnabledLayerNames.data();
    DeviceCreateInfo.enabledExtensionCount = static_cast<std::uint32_t>(EnabledExtensionNames.size());
    DeviceCreateInfo.ppEnabledExtensionNames = EnabledExtensionNames.data();
    DeviceCreateInfo.pEnabledFeatures = &Features;

    const VkResult Result = vkCreateDevice(GPU.get_handle(), &DeviceCreateInfo, nullptr, &handle);

    if (Result == VK_SUCCESS)
    {
        return true;
    }

    return false;
}

kanas::core::device::device(physical_device& InPhysicalDevice) :
    GPU(InPhysicalDevice)
{
}

kanas::core::device::~device()
{

}

std::shared_ptr<kanas::core::queue> kanas::core::device::GetQueue(std::uint32_t InQueueFamilyIndex, std::uint32_t InQueueIndex)
{
    std::shared_ptr<queue> NewQueue = std::make_shared<queue>(*this);

    if (NewQueue && NewQueue->alllocate(InQueueFamilyIndex, InQueueIndex))
    {
        return NewQueue;
    }

    return nullptr;
}

std::shared_ptr<kanas::core::buffer> kanas::core::device::CreateBuffer(std::uint64_t InSize, buffer_usage_flags Usage, std::shared_ptr<FConcurrentGuide> ConcurrentGuide)
{
    if (const auto NewBuffer = std::make_shared<buffer>(*this))
    {
        if (NewBuffer->alllocate(InSize, Usage, ConcurrentGuide))
        {
            return NewBuffer;
        }
    }

    return nullptr;
}

std::shared_ptr<kanas::core::buffer_view> kanas::core::device::Createbuffer_view(std::shared_ptr<buffer> Buffer, VkFormat Format, VkDeviceSize Offset, VkDeviceSize Range)
{
    if (const auto Newbuffer_view = std::make_shared<buffer_view>(*this))
    {
        if (Newbuffer_view->alllocate(Buffer, Format, Offset, Range))
        {
            return Newbuffer_view;
        }
    }

    return nullptr;
}

std::shared_ptr<kanas::core::image > kanas::core::device::CreateImage()
{
    if (const auto NewImage = std::make_shared<image>(*this))
    {
        
    }
    
    return nullptr;
}

std::shared_ptr<kanas::core::image_view> kanas::core::device::CreateImageView(std::shared_ptr<image> Image, VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange)
{
    if (const auto NewImageView = std::make_shared<image_view>(*this))
    {
        if (NewImageView->alllocate(Image, InViewType, InFormat, InComponents, InSubresourceRange))
        {
            return NewImageView;
        }
    }

    return nullptr;
}

kanas::core::descriptor_pool* kanas::core::device::CreateDescriptorPool()
{
    if (const auto NewDescriptorPool = std::make_shared<descriptor_pool>(*this))
    {
    }

    return nullptr;
}

std::shared_ptr<kanas::core::shader_module> kanas::core::device::CreateShaderModule(const std::vector<std::uint32_t>& ShaderCode)
{
    if (const auto NewShaderModule = std::make_shared<shader_module>(*this))
    {
        if (NewShaderModule->alllocate(ShaderCode))
        {
            return NewShaderModule;
        }
    }
    return nullptr;
}

std::shared_ptr<kanas::core::render_pass> kanas::core::device::create_render_pass()
{
    const auto new_render_pass = std::make_shared<render_pass>(*this);
    if(new_render_pass && new_render_pass->allocate())

    return std::shared_ptr<render_pass>();
}

std::shared_ptr<kanas::core::fence> kanas::core::device::CreateFence(bool IsDefaultSignaled)
{
    const auto NewFence = std::make_shared<fence>(*this);

    if (NewFence && NewFence->alllocate(IsDefaultSignaled))
    {
        return NewFence;
    }

    return nullptr;
}

std::shared_ptr<kanas::core::semaphore> kanas::core::device::CreateSemaphore()
{
    if (const auto NewSemaphore = std::make_shared<semaphore>(*this))
    {
        if (NewSemaphore->alllocate(VK_SEMAPHORE_TYPE_BINARY, 0))
        {
            return NewSemaphore;
        }
    }
    return nullptr;
}

std::shared_ptr<kanas::core::FEvent> kanas::core::device::CreateEvent()
{
    if (const auto NewEvent = std::make_shared<FEvent>(*this))
    {
        if (NewEvent->alllocate())
        {
            return NewEvent;
        }
    }
    return nullptr;
}

std::shared_ptr<kanas::core::sampler> kanas::core::device::CreateSampler()
{
    if (const auto NewSampler = std::make_shared<sampler>(*this))
    {
        if (NewSampler->alllocate())
        {
            return NewSampler;
        }
    }
    return nullptr;
}

#include "device.h"
#include "physical_device.h"
#include "queue.h"
#include "fence.h"
#include "semaphore.h"
#include "event.h"
#include "command_buffer.h"
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


bool kanas::core::device::allocate()
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

std::shared_ptr<kanas::core::queue> kanas::core::device::get_queue(std::uint32_t queue_family_index, std::uint32_t queue_index)
{
    std::shared_ptr<queue> _new_queue = std::make_shared<queue>(*this);

    if (_new_queue && _new_queue->allocate(queue_family_index, queue_index))
    {
        return _new_queue;
    }

    return nullptr;
}

std::shared_ptr<kanas::core::buffer> kanas::core::device::create_buffer(std::uint64_t size, buffer_usage_flags usage, std::shared_ptr<FConcurrentGuide> concurrent_guide)
{
    if (const auto _new_buffer = std::make_shared<buffer>(*this))
    {
        if (_new_buffer->alllocate(size, usage, concurrent_guide))
        {
            return _new_buffer;
        }
    }

    return nullptr;
}

std::shared_ptr<kanas::core::buffer_view> kanas::core::device::create_buffer_view(std::shared_ptr<buffer> target, VkFormat format, VkDeviceSize offset, VkDeviceSize range)
{
    if (const auto _new_buffer_view = std::make_shared<buffer_view>(*this))
    {
        if (_new_buffer_view->allocate(target, format, offset, range))
        {
            return _new_buffer_view;
        }
    }

    return nullptr;
}

std::shared_ptr<kanas::core::image > kanas::core::device::create_image()
{
    if (const auto NewImage = std::make_shared<image>(*this))
    {
        
    }
    
    return nullptr;
}

std::shared_ptr<kanas::core::image_view> kanas::core::device::create_image_view(std::shared_ptr<image> Image, VkImageViewType InViewType, VkFormat InFormat, const VkComponentMapping& InComponents, const VkImageSubresourceRange& InSubresourceRange)
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

kanas::core::descriptor_pool* kanas::core::device::create_descriptor_pool()
{
    if (const auto NewDescriptorPool = std::make_shared<descriptor_pool>(*this))
    {
    }

    return nullptr;
}

std::shared_ptr<kanas::core::shader_module> kanas::core::device::create_shader_module(const std::vector<std::uint32_t>& ShaderCode)
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

std::shared_ptr<kanas::core::fence> kanas::core::device::create_fence(bool IsDefaultSignaled)
{
    const auto _new_fence = std::make_shared<fence>(*this);

    if (_new_fence && _new_fence->allocate(IsDefaultSignaled))
    {
        return _new_fence;
    }

    return nullptr;
}

std::shared_ptr<kanas::core::semaphore> kanas::core::device::create_semaphore()
{
    if (const auto _new_semaphore = std::make_shared<semaphore>(*this))
    {
        if (_new_semaphore->allocate(VK_SEMAPHORE_TYPE_BINARY, 0))
        {
            return _new_semaphore;
        }
    }
    return nullptr;
}

std::shared_ptr<kanas::core::FEvent> kanas::core::device::create_event()
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

#include "BufferView.h"
#include "Buffer.h"
#include "Device.h"

Kanas::Core::BufferView::BufferView(Device& InDevice) :
    DeviceObject(InDevice)
{
}

Kanas::Core::BufferView::~BufferView()
{
    if (IsValid())
    {
        vkDestroyBufferView(GetDevice().GetHandle(), GetHandle(), nullptr);

        ResetHandle();
    }
}

bool Kanas::Core::BufferView::Allocate(Buffer* InBuffer, VkFormat InFormat, VkDeviceSize InOffset, VkDeviceSize InRange)
{
    VkBufferViewCreateInfo BufferViewCreateInfo;
    BufferViewCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    BufferViewCreateInfo.pNext = nullptr;
    BufferViewCreateInfo.flags = {};
    BufferViewCreateInfo.buffer = InBuffer->GetHandle();
    BufferViewCreateInfo.format = InFormat;
    BufferViewCreateInfo.offset = InOffset;
    BufferViewCreateInfo.range = InRange;


    VkResult Result = vkCreateBufferView(GetDevice().GetHandle(), &BufferViewCreateInfo, nullptr, &_Handle);

    if (Result == VkResult::VK_SUCCESS)
    {
        Target = InBuffer;
        return true;
    }

    return false;
}

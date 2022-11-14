#include "BufferView.h"
#include "Buffer.h"
#include "Device.h"

Kanas::Core::FBufferView::FBufferView(FDevice& InDevice) :
    FDeviceObject(InDevice)
{
}

Kanas::Core::FBufferView::~FBufferView()
{
    if (IsValid())
    {
        vkDestroyBufferView(GetDevice().GetHandle(), GetHandle(), nullptr);

        ResetHandle();
    }
}

bool Kanas::Core::FBufferView::Allocate(TSharedPtr<FBuffer> InBuffer, VkFormat InFormat, VkDeviceSize InOffset, VkDeviceSize InRange)
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
        Buffer = InBuffer;
        return true;
    }

    return false;
}

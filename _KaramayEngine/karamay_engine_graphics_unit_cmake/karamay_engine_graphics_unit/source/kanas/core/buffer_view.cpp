#include "buffer_view.h"
#include "buffer.h"
#include "device.h"

kanas::core::buffer_view::buffer_view(device& owner) :
    device_object(owner)
{
}

kanas::core::buffer_view::~buffer_view()
{
    if (IsValid())
    {
        vkDestroyBufferView(get_device().get_handle(), get_handle(), nullptr);

        reset_handle();
    }
}

bool kanas::core::buffer_view::allocate(std::shared_ptr<buffer> InBuffer, VkFormat InFormat, VkDeviceSize InOffset, VkDeviceSize InRange)
{
    VkBufferViewCreateInfo bufferViewCreateInfo;
    bufferViewCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    bufferViewCreateInfo.pNext = nullptr;
    bufferViewCreateInfo.flags = {};
    bufferViewCreateInfo.buffer = InBuffer->get_handle();
    bufferViewCreateInfo.format = InFormat;
    bufferViewCreateInfo.offset = InOffset;
    bufferViewCreateInfo.range = InRange;

    VkResult Result = vkCreateBufferView(get_device().get_handle(), &bufferViewCreateInfo, nullptr, &handle);

    if (Result == VkResult::VK_SUCCESS)
    {
        return true;
    }

    return false;
}

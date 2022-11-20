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

bool kanas::core::buffer_view::alllocate(std::shared_ptr<buffer> InBuffer, VkFormat InFormat, VkDeviceSize InOffset, VkDeviceSize InRange)
{
    Vkbuffer_viewCreateInfo buffer_viewCreateInfo;
    buffer_viewCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_VIEW_CREATE_INFO;
    buffer_viewCreateInfo.pNext = nullptr;
    buffer_viewCreateInfo.flags = {};
    buffer_viewCreateInfo.buffer = InBuffer->get_handle();
    buffer_viewCreateInfo.format = InFormat;
    buffer_viewCreateInfo.offset = InOffset;
    buffer_viewCreateInfo.range = InRange;

    VkResult Result = vkCreateBuffer(get_device().get_handle(), &buffer_viewCreateInfo, nullptr, &handle);

    if (Result == VkResult::VK_SUCCESS)
    {
        Buffer = InBuffer;
        return true;
    }

    return false;
}

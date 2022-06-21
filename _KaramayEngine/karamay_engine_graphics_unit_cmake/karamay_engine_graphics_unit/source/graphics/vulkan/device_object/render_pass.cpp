#include "render_pass.h"
#include "pooled_object/command_buffer.h"
#include "framebuffer.h"

vk_render_pass::vk_render_pass(vk_device& dev) : device_object(dev)
{
}

vk_render_pass::~vk_render_pass()
{
    deallocate();
}

bool vk_render_pass::allocate(const std::vector<VkAttachmentDescription>& attachments, const std::vector<VkSubpassDependency>& dependencies, const std::vector<VkSubpassDescription>& subpasses)
{
    VkRenderPassCreateInfo _create_info;
    _create_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    _create_info.flags;
    _create_info.attachmentCount = attachments.size();
    _create_info.dependencyCount = dependencies.size();
    _create_info.subpassCount = subpasses.size();
    _create_info.pAttachments = attachments.data();
    _create_info.pDependencies = dependencies.data();
    _create_info.pSubpasses = subpasses.data();
    auto _ret = vkCreateRenderPass(_dev.handle(), &_create_info, nullptr, &_handle);
    if (_ret != VkResult::VK_SUCCESS)
    {
        return false;
    }
    return true;
}

void vk_render_pass::deallocate()
{
    if (_handle)
    {
        vkDestroyRenderPass(_dev.handle(), _handle, nullptr);
        _handle = nullptr;
    }
}

void vk_render_pass::set(const std::function<void(framebuffer*, vk_command_buffer*)>& sequence)
{
    command_buffer* _recorder = nullptr;
    framebuffer* _rt = nullptr;
    _begin(_recorder, _rt, {}, {}, VkSubpassContents::VK_SUBPASS_CONTENTS_INLINE);
    sequence(_rt, _recorder);
    _end(_recorder);
}

void vk_render_pass::_begin(vk_command_buffer* recorder, framebuffer* render_target, const std::vector<VkClearValue>& clear_values, VkRect2D render_area, VkSubpassContents contents)
{
    VkRenderPassBeginInfo _begin_info;
    _begin_info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    _begin_info.framebuffer = render_target->handle();
    _begin_info.renderPass = _handle;
    _begin_info.clearValueCount = clear_values.size();
    _begin_info.pClearValues = clear_values.data();
    _begin_info.renderArea = render_area;

    vkCmdBeginRenderPass(recorder->handle(), &_begin_info, contents);

}

void vk_render_pass::_end(vk_command_buffer* recorder)
{
    vkCmdEndRenderPass(recorder->handle());
}

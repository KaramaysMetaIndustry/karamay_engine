#include "render_pass.h"
#include "framebuffer.h"
#include "pipeline.h"
#include "command_buffer.h"
#include "attachment.h"
#include "image_view.h"
#include "image.h"
#include "subpass.h"
#include "device.h"

bool kanas::core::render_pass::allocate(
    const framebuffer_info& render_target_info, 
    const default_subpass_info& default_subpass, 
    const subpass_extension& extension)
{
    std::vector<VkAttachmentDescription> raw_attchment_descriptions;
    for (const auto& attachment_view : render_target_info.attachment_views)
    {
        VkAttachmentDescription desc;
        desc.flags;
        desc.format;
        desc.samples;
        desc.loadOp;
        desc.storeOp;
        desc.stencilLoadOp;
        desc.stencilStoreOp;
        desc.initialLayout;
        desc.finalLayout;

        raw_attchment_descriptions.emplace_back(desc);
    }

    const auto& _subpasses = _linker.get_subpasses();
    
    std::vector<VkSubpassDescription> raw_subpasses;

    for (const auto& sub : _subpasses)
    {
        VkSubpassDescription desc;
        desc.flags = {};
        desc.pipelineBindPoint;
        desc.inputAttachmentCount;
        desc.pInputAttachments;
        desc.colorAttachmentCount;
        desc.pColorAttachments;
        desc.pResolveAttachments;
        desc.pDepthStencilAttachment;
        desc.preserveAttachmentCount;
        desc.pPreserveAttachments;

        raw_subpasses.emplace_back(desc);
    }

    std::vector<std::shared_ptr<subpass_dependency>> subpass_dependencies;
    _linker.get_denpendencies(subpass_dependencies);
    std::vector<VkSubpassDependency> raw_subpass_dependencies;

    VkRenderPassCreateInfo renderPassCreateInfo{};
    renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassCreateInfo.flags = {};
    renderPassCreateInfo.attachmentCount = raw_attchment_descriptions.size();
    renderPassCreateInfo.pAttachments = raw_attchment_descriptions.data();
    renderPassCreateInfo.subpassCount = raw_subpasses.size();
    renderPassCreateInfo.pSubpasses = raw_subpasses.data();
    renderPassCreateInfo.dependencyCount = raw_subpass_dependencies.size();
    renderPassCreateInfo.pDependencies = raw_subpass_dependencies.data();

    if (vkCreateRenderPass(get_device().get_handle(), &renderPassCreateInfo, nullptr, &handle) != VK_SUCCESS)
    {
        return false;
    }

    std::vector<std::shared_ptr<image_view>> attchments;
    for (const auto& attachment_view : render_target_info.attachment_views)
    {
        attchments.emplace_back(attachment_view->img);
    }

    auto new_framebuffer = std::make_unique<framebuffer>(get_device());
    if (new_framebuffer && new_framebuffer->alllocate(*this, 
        render_target_info.width, 
        render_target_info.height, 
        render_target_info.layers, 
        attchments))
    {
        _render_target = std::move(new_framebuffer);

        return true;
    }

    return false;
}

kanas::core::render_pass::render_pass(device& owner) :
    device_object(owner)
{
    framebuffer_info _render_target_info;
    _render_target_info.width = 1024;
    _render_target_info.height = 1024;
    _render_target_info.layers = 1;
    _render_target_info.attachment_views;

    default_subpass_info _default_subpass;

    const bool result = allocate(_render_target_info, _default_subpass, 
        [](subpass_linker& linker) 
        {
            linker.plus(nullptr);
            linker.plus({});

            return true; 
        }
    );
}

kanas::core::render_pass::render_pass(render_pass& other) :
    device_object(other.get_device())
{
}

kanas::core::render_pass::~render_pass()
{
    if (IsValid())
    {
        vkDestroyRenderPass(get_device().get_handle(), get_handle(), nullptr);
        reset_handle();
    }
}

void kanas::core::render_pass::cmd_execute(primary_command_buffer& pcb)
{

}

void kanas::core::render_pass::clean_state()
{
    _is_dirty = false;
}

void kanas::core::render_pass::set_render_area(const VkRect2D& val)
{
    _render_area = val;
    _is_dirty = true;
}

void kanas::core::render_pass::set_clear_values(const std::vector<VkClearValue>& vals)
{
    _clear_values = vals;
    _is_dirty = true;
}

kanas::core::subpass_linker::subpass_linker(std::shared_ptr<subpass> default_subpass)
{
    _subpasses.push_back(default_subpass);
}

void kanas::core::subpass_linker::plus(std::shared_ptr<subpass> next)
{
    if (!next)
    {
        return;
    }

    _subpasses.push_back(next);

    //        VkSubpassDescription Subpass{};
   //        Subpass.flags = {};
   //        Subpass.pipelineBindPoint = Pipeline->GetBindPoint();
   //        Subpass.inputAttachmentCount;
   //        Subpass.pInputAttachments;
   //        Subpass.colorAttachmentCount;
   //        Subpass.pColorAttachments;
   //        Subpass.pResolveAttachments;
   //        Subpass.pDepthStencilAttachment;
   //        Subpass.preserveAttachmentCount;
   //        Subpass.pPreserveAttachments;

   //        VkSubpassDependency SubpassDependency{};
   //        SubpassDependency.srcSubpass = 0;
   //        SubpassDependency.dstSubpass = 0;
   //        SubpassDependency.srcStageMask = pipelineStageFlags().SetTransfer().Get();
   //        SubpassDependency.dstStageMask = pipelineStageFlags().SetFragmentShader().Get();
   //        SubpassDependency.srcAccessMask = FAccessFlags().SetTransferWrite().Get();
   //        SubpassDependency.dstAccessMask = FAccessFlags().SetColorAttachmentRead().Get();
   //        SubpassDependency.dependencyFlags = FDependencyFlags().SetViewLocal().Get();
}

void kanas::core::subpass_linker::clear()
{
}

void kanas::core::subpass_linker::get_dependencies(std::vector<std::shared_ptr<subpass_dependency>>& out_dependencies)
{
}

void kanas::core::mobile_render_pass::cmd_execute(kanas::core::primary_command_buffer &pcb) 
{
    std::vector<subpass*> _subpasses;
    _subpasses.reserve(1 + _extended_subpasses.size());

    checkf(_fixed_subpass, "default subpass is invalid");
    _subpasses.push_back(_fixed_subpass.get());

    for (const auto& _extension : _extended_subpasses)
    {
        check(_extension);
        _subpasses.push_back(_extension.get());
    }

    const std::size_t _num_of_subpasses = _subpasses.size();

    std::vector<std::shared_ptr<secondary_command_buffer>> _scbs;

    if (_scbs.size() != _num_of_subpasses)
    {
        std::cerr << "can not find enough scbs" << std::endl;
        return;
    }

    for (std::size_t _idx = 0; _idx < _num_of_subpasses; ++_idx)
    {
        check(_scbs[_idx]);
        _scbs[_idx]->record(*_subpasses[_idx]);
    }

    VkRenderPassBeginInfo renderPassBeginInfo{};
    renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo.framebuffer = _render_target->get_handle();
    renderPassBeginInfo.renderPass = get_handle();
    renderPassBeginInfo.clearValueCount = _clear_values.size();
    renderPassBeginInfo.pClearValues = _clear_values.data();
    renderPassBeginInfo.renderArea = _render_area;

    std::vector<VkCommandBuffer> _raw_scbs;
    //get_raw(_scbs, _raw_scbs);

    pcb.reset();

    vkCmdBeginRenderPass(pcb.get_handle(), &renderPassBeginInfo, _subpasses[0]->get_contents());

    for (std::size_t _idx = 0; _idx < _raw_scbs.size(); ++_idx)
    {
        if (_idx != 0)
        {
            vkCmdNextSubpass(pcb.get_handle(), _subpasses[_idx]->get_contents());
        }
        vkCmdExecuteCommands(pcb.get_handle(), 1, _raw_scbs.data());
    }

    vkCmdEndRenderPass(pcb.get_handle());
}

kanas::core::mobile_render_pass::mobile_render_pass(device& dev) : render_pass(dev) {

}

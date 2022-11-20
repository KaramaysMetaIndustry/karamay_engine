#include "render_pass.h"
#include "device.h"
#include "command_buffer.h"
#include "framebuffer.h"
#include "pipeline.h"
#include "attachment.h"
#include "image_view.h"
#include "image.h"
#include "subpass.h"

bool kanas::core::render_pass::allocate(
    const framebuffer_info& render_target_info, 
    const default_subpass_info& default_subpass, 
    const subpass_extension& extension)
{
    bool result = false;

    extension(_linker);

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

    std::vector<std::shared_ptr<subpass>> subpasses;
    _linker.get_subpasses(subpasses);
    std::vector<VkSubpassDescription> raw_subpasses;

    for (const auto& sub : subpasses)
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

    VkRenderPassCreateInfo RenderPassCreateInfo{};
    RenderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    RenderPassCreateInfo.flags = {};
    RenderPassCreateInfo.attachmentCount = raw_attchment_descriptions.size();
    RenderPassCreateInfo.pAttachments = raw_attchment_descriptions.data();
    RenderPassCreateInfo.subpassCount = raw_subpasses.size();
    RenderPassCreateInfo.pSubpasses = raw_subpasses.data();
    RenderPassCreateInfo.dependencyCount = raw_subpass_dependencies.size();
    RenderPassCreateInfo.pDependencies = raw_subpass_dependencies.data();

    VkResult RenderPassCreationResult = vkCreateRenderPass(get_device().get_handle(), &RenderPassCreateInfo, nullptr, &handle);

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
    device_object(owner), 
    _linker(nullptr)
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

            return true; 
        }
    );
}

kanas::core::render_pass::~render_pass()
{
    if (IsValid())
    {
        vkDestroyRenderPass(get_device().get_handle(), get_handle(), nullptr);
        reset_handle();
    }
}

void kanas::core::render_pass::cmd_execute(primary_command_buffer& recorder)
{
    VkRenderPassBeginInfo RenderPassBeginInfo{};
    RenderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassBeginInfo.framebuffer = _render_target->get_handle();
    RenderPassBeginInfo.renderPass = get_handle();
    RenderPassBeginInfo.clearValueCount = _clear_values.size();
    RenderPassBeginInfo.pClearValues = _clear_values.data();
    RenderPassBeginInfo.renderArea = _render_area;

    recorder.reset(command_buffer_reset_flags().set_release_resources());

    std::vector<std::shared_ptr<subpass>> _subpasses;
    _linker.get_subpasses(_subpasses);

    std::vector<std::shared_ptr<secondary_command_buffer>> SubCmdBuffers;
    recorder.get_secondary_command_buffers(_subpasses.size(), SubCmdBuffers);

    for (size_t index = 1; index < _subpasses.size(); ++index)
    {
        SubCmdBuffers[index - 1]->record(_subpasses[index]);
    }

    std::vector<VkCommandBuffer> SubCmdBufferHandles;
    get_raw(SubCmdBuffers, SubCmdBufferHandles);

    vkCmdBeginRenderPass(recorder.get_handle(), &RenderPassBeginInfo, _subpasses[0]->get_contents());
    
    for (std::uint64_t index = 0; index < SubCmdBufferHandles.size(); ++index)
    {
        if (index != 0)
        {
            vkCmdNextSubpass(recorder.get_handle(), _subpasses[index]->get_contents());
        }
        vkCmdExecuteCommands(recorder.get_handle(), 1, SubCmdBufferHandles.data());
    }
    
    vkCmdEndRenderPass(recorder.get_handle());
}

void kanas::core::render_pass::clean()
{
    _is_dirty = false;
}

void kanas::core::render_pass::set_render_area(const VkRect2D& val)
{
    render_area = val;
    _is_dirty = true;
}

void kanas::core::render_pass::set_clear_values(const std::vector<VkClearValue>& vals)
{
    clear_values = vals;
    _is_dirty = true;
}

kanas::core::subpass_linker::subpass_linker(std::shared_ptr<subpass> root)
{
}

void kanas::core::subpass_linker::plus(std::shared_ptr<subpass> next)
{
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

void kanas::core::subpass_linker::get_subpasses(std::vector<std::shared_ptr<subpass>>& out_subpasses)
{
}

void kanas::core::subpass_linker::get_denpendencies(std::vector<std::shared_ptr<subpass_dependency>>& out_dependencies)
{
}

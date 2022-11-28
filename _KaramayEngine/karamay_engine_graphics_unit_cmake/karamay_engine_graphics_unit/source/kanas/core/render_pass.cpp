#include "render_pass.h"
#include "framebuffer.h"
#include "pipeline.h"
#include "command_buffer.h"
#include "image_view.h"
#include "image.h"
#include "subpass.h"
#include "device.h"
#include "pipeline.h"

_KANAS_CORE_BEGIN

struct render_pass_static_helper
{
    static void get_raw(const std::vector<attachment>& attachments, std::vector<VkAttachmentDescription>& rawAttachmentDescriptions)
    {
        rawAttachmentDescriptions.reserve(attachments.size());
        for(const auto& attachment : attachments)
        {
            VkAttachmentDescription desc{};
            desc.flags = {};
            desc.format = attachment.format;
            desc.samples = attachment.samples.raw();
            desc.loadOp= attachment.load_op.raw();
            desc.storeOp = attachment.store_op.raw();
            desc.stencilLoadOp = attachment.stencil_load_op.raw();
            desc.stencilStoreOp = attachment.stencil_store_op.raw();
            desc.initialLayout = attachment.initial_layout.raw();
            desc.finalLayout = attachment.final_layout.raw();

            rawAttachmentDescriptions.emplace_back(desc);
        }
    }

    static void get_raw(const subpass_list& list, std::vector<VkSubpassDescription>& rawSubpassDescriptions, std::vector<VkSubpassDependency>& rawSubpassDependencies)
    {
        {
            VkAttachmentReference attachmentRef;
            attachmentRef.attachment = 0;
            attachmentRef.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

            std::vector<VkAttachmentReference> inputAttachments =
                    {
                            attachmentRef
                    };

            std::vector<VkAttachmentReference> colorAttachments =
                    {

                    };

            VkSubpassDescription _subpassDescription;
            _subpassDescription.flags = {};
            _subpassDescription.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;
            _subpassDescription.inputAttachmentCount = static_cast<std::uint32_t>(inputAttachments.size());
            _subpassDescription.pInputAttachments = inputAttachments.data();
            _subpassDescription.colorAttachmentCount = static_cast<std::uint32_t>(colorAttachments.size());
            _subpassDescription.pColorAttachments = colorAttachments.data();
            _subpassDescription.pResolveAttachments;
            _subpassDescription.pDepthStencilAttachment;
            _subpassDescription.preserveAttachmentCount;
            _subpassDescription.pPreserveAttachments;
        }
    }


};


_KANAS_CORE_END

bool kanas::core::render_pass::allocate(const std::vector<attachment>& attachments, const subpass_list& subpasses)
{
    // check


    std::vector<VkAttachmentDescription> _rawAttachmentDescriptions;
    render_pass_static_helper::get_raw(attachments, _rawAttachmentDescriptions);

    std::vector<VkSubpassDescription> _rawSubpassDescriptions;
    std::vector<VkSubpassDependency> _rawSubpassDependencies;

    render_pass_static_helper::get_raw(subpasses, _rawSubpassDescriptions, _rawSubpassDependencies);

    VkRenderPassCreateInfo renderPassCreateInfo{};
    renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    renderPassCreateInfo.flags = {};
    renderPassCreateInfo.attachmentCount = _rawAttachmentDescriptions.size();
    renderPassCreateInfo.pAttachments = _rawAttachmentDescriptions.data();
    renderPassCreateInfo.subpassCount = _rawSubpassDescriptions.size();
    renderPassCreateInfo.pSubpasses = _rawSubpassDescriptions.data();
    renderPassCreateInfo.dependencyCount = _rawSubpassDependencies.size();
    renderPassCreateInfo.pDependencies = _rawSubpassDependencies.data();

    if (vkCreateRenderPass(get_device().get_handle(), &renderPassCreateInfo, nullptr, &handle) == VK_SUCCESS)
    {
        return true;
    }

    return false;
}

bool kanas::core::render_pass::allocate(const kanas::core::render_pass_obj_model &obj_model)
{
    _name = obj_model.name;

    subpass_list _subpass_list(obj_model.default_subpass);
    for(const auto& pair : obj_model.next_subpasses)
    {
        _subpass_list.plus(pair.first, pair.second);
    }

    return allocate(obj_model.attachments, _subpass_list);
}

kanas::core::render_pass::render_pass(device& owner) :
    device_object(owner)
{
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

void kanas::core::render_pass::cmd_execute(primary_command_buffer& pcb) const
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
    renderPassBeginInfo.framebuffer = _current_render_target->get_handle();
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

void kanas::core::render_pass::set_render_area(const VkRect2D& val)
{
    _render_area = val;
}

void kanas::core::render_pass::set_clear_values(const std::vector<VkClearValue>& vals)
{
    _clear_values = vals;
}

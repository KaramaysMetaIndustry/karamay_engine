#include "RenderPass.h"
#include "Device.h"
#include "CommandBuffer.h"
#include "Framebuffer.h"

Kanas::Core::RenderPass::RenderPass(Device& InDevice) :
    DeviceObject(InDevice)
{
}

Kanas::Core::RenderPass::~RenderPass()
{
    if (IsValid())
    {
        vkDestroyRenderPass(GetDevice().GetHandle(), GetHandle(), nullptr);

        ResetHandle();
    }
}

bool Kanas::Core::RenderPass::Allocate(const std::vector<VkAttachmentDescription>& InAttachments, const std::vector<VkSubpassDescription>& InSubpasses, const std::vector<VkSubpassDependency>& InSubpassDependencies)
{
    VkSubpassDescription Subpass;
    Subpass.flags;
    Subpass.pipelineBindPoint;
    Subpass.inputAttachmentCount;
    Subpass.pInputAttachments;
    Subpass.colorAttachmentCount;
    Subpass.pColorAttachments;
    Subpass.pResolveAttachments;
    Subpass.pDepthStencilAttachment;
    Subpass.preserveAttachmentCount;
    Subpass.pPreserveAttachments;

    VkSubpassDependency SubpassDependency;
    SubpassDependency.srcSubpass = 0;
    SubpassDependency.dstSubpass = 0;
    SubpassDependency.srcStageMask = VkPipelineStageFlagBits::VK_PIPELINE_STAGE_TRANSFER_BIT;
    SubpassDependency.dstStageMask;
    SubpassDependency.srcAccessMask;
    SubpassDependency.dstAccessMask;
    SubpassDependency.dependencyFlags;

    VkRenderPassCreateInfo RenderPassCreateInfo;
    RenderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    RenderPassCreateInfo.flags = {};
    RenderPassCreateInfo.attachmentCount = InAttachments.size();
    RenderPassCreateInfo.pAttachments = InAttachments.data();
    RenderPassCreateInfo.subpassCount = InSubpasses.size();
    RenderPassCreateInfo.pSubpasses = InSubpasses.data();
    RenderPassCreateInfo.dependencyCount = InSubpassDependencies.size();
    RenderPassCreateInfo.pDependencies = InSubpassDependencies.data();
   

    VkResult Result = vkCreateRenderPass(GetDevice().GetHandle(), &RenderPassCreateInfo, nullptr, &_Handle);
    
    if (Result == VkResult::VK_SUCCESS)
    {
        return true;
    }
    return false;
}

void Kanas::Core::RenderPass::CmdCollect(CommandBuffer& InRecorder)
{
    VkRenderPassBeginInfo RenderPassBeginInfo;
    RenderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassBeginInfo.framebuffer = RenderTarget->GetHandle();
    RenderPassBeginInfo.renderPass = _Handle;
    RenderPassBeginInfo.clearValueCount = ClearValues.size();
    RenderPassBeginInfo.pClearValues = ClearValues.data();
    RenderPassBeginInfo.renderArea = RenderArea;

    vkCmdBeginRenderPass(InRecorder.GetHandle(), &RenderPassBeginInfo, SubpassContents);
    
    Sequence(InRecorder, *RenderTarget);
    
    vkCmdEndRenderPass(InRecorder.GetHandle());
}

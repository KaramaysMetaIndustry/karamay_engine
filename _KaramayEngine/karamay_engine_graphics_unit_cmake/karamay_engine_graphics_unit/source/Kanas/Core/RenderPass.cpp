#include "RenderPass.h"
#include "Device.h"
#include "CommandBuffer.h"
#include "Framebuffer.h"

bool Kanas::Core::FRenderPass::Allocate(const TVector<VkAttachmentDescription>& InAttachments, const TVector<VkSubpassDescription>& InSubpasses, const TVector<VkSubpassDependency>& InSubpassDependencies)
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

Kanas::Core::FRenderPass::FRenderPass(FDevice& InDevice) :
    FDeviceObject(InDevice)
{
}

Kanas::Core::FRenderPass::~FRenderPass()
{
    if (IsValid())
    {
        vkDestroyRenderPass(GetDevice().GetHandle(), GetHandle(), nullptr);

        ResetHandle();
    }
}

void Kanas::Core::FRenderPass::CmdCollect(FCommandBuffer& InRecorder)
{
    VkRenderPassBeginInfo RenderPassBeginInfo;
    RenderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassBeginInfo.framebuffer = Framebuffer->GetHandle();
    RenderPassBeginInfo.renderPass = _Handle;
    RenderPassBeginInfo.clearValueCount = ClearValues.size();
    RenderPassBeginInfo.pClearValues = ClearValues.data();
    RenderPassBeginInfo.renderArea = RenderArea;

    vkCmdBeginRenderPass(InRecorder.GetHandle(), &RenderPassBeginInfo, SubpassContents);
    
    Sequence(InRecorder, *Framebuffer);
    
    vkCmdEndRenderPass(InRecorder.GetHandle());
}

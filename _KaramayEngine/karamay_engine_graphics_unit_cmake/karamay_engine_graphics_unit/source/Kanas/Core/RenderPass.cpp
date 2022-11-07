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
    VkRenderPassCreateInfo RenderPassCreateInfo;
    RenderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    RenderPassCreateInfo.flags;
    RenderPassCreateInfo.attachmentCount = InAttachments.size();
    RenderPassCreateInfo.dependencyCount = InSubpassDependencies.size();
    RenderPassCreateInfo.subpassCount = InSubpasses.size();
    RenderPassCreateInfo.pAttachments = InAttachments.data();
    RenderPassCreateInfo.pDependencies = InSubpassDependencies.data();
    RenderPassCreateInfo.pSubpasses = InSubpasses.data();

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

#include "RenderPass.h"
#include "Device.h"
#include "CommandBuffer.h"
#include "Framebuffer.h"
#include "Pipeline.h"
#include "Attachment.h"
#include "ImageView.h"
#include "Image.h"
#include "Subpass.h"

bool Kanas::Core::FRenderPass::Allocate(const TVector<TSharedPtr<FSubpass>>& InSubpasses, const TVector<VkSubpassDependency>& InSubpassDependencies)
{
    //[]() // Create Framebuffer
        //{
        //    


        //    RawCreateFramebuffer(Attachments);


        //    for (const auto& Attachment : Attachments)
        //    {

        //    }


        //    TVector<VkAttachmentDescription> InAttachments;

        //    VkAttachmentDescription AttachmentDescription{};
        //    AttachmentDescription.flags = {};
        //    AttachmentDescription.format = Attachment->ImageView->GetViewFormat();
        //    AttachmentDescription.samples = Attachment->SampleCount;
        //    AttachmentDescription.loadOp = Attachment->LoadOp;
        //    AttachmentDescription.storeOp = Attachment->StoreOp;
        //    AttachmentDescription.stencilLoadOp = Attachment->StencilLoadOp;
        //    AttachmentDescription.stencilStoreOp = Attachment->StencilStoreOp;
        //    AttachmentDescription.initialLayout = Attachment->ImageView->GetImage()->GetLayout();
        //    AttachmentDescription.finalLayout;

        //    VkAttachmentReference Reference;
        //    Reference.attachment;
        //    Reference.layout;

        //    return false; 
        //},

    TVector<TSharedPtr<FAttachment>> Attachments;

    return Allocate(
        Attachments,
        
        [](const FFramebuffer& RenderTarget, TVector<TUniquePtr<FSubpass>>& OutSubpasses) // Create Subpasses
        { 
            TSharedPtr<FPipeline> Pipeline;

            VkSubpassDescription Subpass{};
            Subpass.flags = {};
            Subpass.pipelineBindPoint = Pipeline->GetBindPoint();
            Subpass.inputAttachmentCount;
            Subpass.pInputAttachments;
            Subpass.colorAttachmentCount;
            Subpass.pColorAttachments;
            Subpass.pResolveAttachments;
            Subpass.pDepthStencilAttachment;
            Subpass.preserveAttachmentCount;
            Subpass.pPreserveAttachments;

            VkSubpassDependency SubpassDependency{};
            SubpassDependency.srcSubpass = 0;
            SubpassDependency.dstSubpass = 0;
            SubpassDependency.srcStageMask = FPipelineStageFlags().SetTransfer().Get();
            SubpassDependency.dstStageMask = FPipelineStageFlags().SetFragmentShader().Get();
            SubpassDependency.srcAccessMask = FAccessFlags().SetTransferWrite().Get();
            SubpassDependency.dstAccessMask = FAccessFlags().SetColorAttachmentRead().Get();
            SubpassDependency.dependencyFlags = FDependencyFlags().SetViewLocal().Get();
            return false; 
        },
        {1024, 1024, 1}
    );

    
    return false;
}

struct FFramebufferDimension
{
    uint32 Width, Height, Layers;
};

bool Kanas::Core::FRenderPass::Allocate(
    const TVector<TSharedPtr<FAttachmentView>>& AttachmentViews, 
    const SubpassCreation& SubpassCreationLambda,
    const FFramebufferDimension& FramebufferDimension
)
{
    bool CreationResult = false;

    if (!CreationResult)
    {
        return false;
    }

    TVector<TUniquePtr<FSubpass>> Subpasses;

    TVector<VkAttachmentDescription> RawAttachments;
    TVector<VkSubpassDescription> RawSubpasses;

    VkRenderPassCreateInfo RenderPassCreateInfo{};
    RenderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
    RenderPassCreateInfo.flags = {};
    RenderPassCreateInfo.attachmentCount = RawAttachments.size();
    RenderPassCreateInfo.pAttachments = RawAttachments.data();
    RenderPassCreateInfo.subpassCount = RawSubpasses.size();
    RenderPassCreateInfo.pSubpasses = RawSubpasses.data();
    RenderPassCreateInfo.dependencyCount = InSubpassDependencies.size();
    RenderPassCreateInfo.pDependencies = InSubpassDependencies.data();

    VkResult Result = vkCreateRenderPass(GetDevice().GetHandle(), &RenderPassCreateInfo, nullptr, &_Handle);

    TVector<TSharedPtr<FImageView>> Attachments;
    Attachments.reserve(AttachmentViews.size());
    for (const auto& AttachmentView : AttachmentViews)
    {
        Attachments.emplace_back(AttachmentView->ImageView);
    }

    FFramebuffer* NewFramebuffer = new FFramebuffer(GetDevice());
    if (NewFramebuffer && NewFramebuffer->Allocate(*this, FramebufferDimension, Attachments))
    {
        Framebuffer.reset(NewFramebuffer);
        
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
    VkRenderPassBeginInfo RenderPassBeginInfo{};
    RenderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    RenderPassBeginInfo.framebuffer = Framebuffer->GetHandle();
    RenderPassBeginInfo.renderPass = GetHandle();
    RenderPassBeginInfo.clearValueCount = ClearValues.size();
    RenderPassBeginInfo.pClearValues = ClearValues.data();
    RenderPassBeginInfo.renderArea = RenderArea;

    vkCmdBeginRenderPass(InRecorder.GetHandle(), &RenderPassBeginInfo, SubpassContents);
    
    Sequence(InRecorder, *Framebuffer);
    
    vkCmdEndRenderPass(InRecorder.GetHandle());
}

void Kanas::Core::FRenderPass::CreateDefaultSubpass()
{
    auto NewSubpass = MakeShared<FSubpass>();
    if (NewSubpass)
    {
        DefaultSubpass = NewSubpass;
    }
}

TSharedPtr<Kanas::Core::FSubpass> Kanas::Core::FRenderPass::GetFinalSubpass() const
{
    TSharedPtr<FSubpass> Root = DefaultSubpass;

    while (Root)
    {
        if (!Root->GetNext())
        {
            return Root;
        }

        Root = Root->GetNext();
    }

    return nullptr;
}

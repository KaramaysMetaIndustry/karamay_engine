#include "subpass.h"
#include "command_buffer.h"
#include "pipeline.h"

kanas::core::subpass::subpass()
{
	std::vector<VkAttachmentReference> inputAttachments;
	std::vector<VkAttachmentReference> colorAttachments;
	std::vector<VkAttachmentReference> resolveAttachments;
	std::vector<VkAttachmentReference> preserveAttachments;

	VkSubpassDescription desc;
	desc.flags = {};
	desc.pipelineBindPoint = pipe->GetBindPoint();
	desc.inputAttachmentCount;
	desc.pInputAttachments;
	desc.colorAttachmentCount;
	desc.pColorAttachments;
	desc.pResolveAttachments;
	desc.pDepthStencilAttachment;
	desc.preserveAttachmentCount;
	desc.pPreserveAttachments;

}

kanas::core::subpass::~subpass()
{
}

void kanas::core::subpass::cmd_execute(secondary_command_buffer& recorder)
{
	record_functor(recorder);
	std::string_view sv;
	std::vector<int> a;
	a.emplace_back();

	std::forward<kanas::core::subpass&&>(*this);


}


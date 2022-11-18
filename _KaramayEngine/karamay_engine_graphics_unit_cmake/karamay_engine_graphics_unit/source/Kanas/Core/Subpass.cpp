#include "Subpass.h"

Kanas::Core::FSubpass::FSubpass(TSharedPtr<FPipeline> InPipeline, const TVector<uint32>& InAttachmentIndices)
{
}

Kanas::Core::FSubpass::~FSubpass()
{
}

void Kanas::Core::FSubpass::SetNext(TSharedPtr<FSubpass> InSubpass, const VkSubpassDependency& InDependency)
{
}

TSharedPtr<Kanas::Core::FSubpass> Kanas::Core::FSubpass::GetNext() const
{
	return Next;
}

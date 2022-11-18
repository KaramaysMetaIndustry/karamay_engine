#ifndef _SUBPASS_H_
#define _SUBPASS_H_

#include "KanasCoreMacros.h"
#include "KanasCoreTypes.h"

_KANAS_CORE_BEGIN

class FRenderPass;
class FPipeline;

class FSubpass
{
public:

	FSubpass(TSharedPtr<FPipeline> InPipeline, const TVector<uint32>& InAttachmentIndices);

	virtual ~FSubpass();

	void SetNext(TSharedPtr<FSubpass> InSubpass, const VkSubpassDependency& InDependency);

	TSharedPtr<FSubpass> GetNext() const;

private:

	TSharedPtr<FSubpass> Next;

	TSharedPtr<FPipeline> Pipeline;

};

struct FSubpassDependency
{
	FPipelineStageFlags PreStageMask{};

	FPipelineStageFlags StageMask{};

	FAccessFlags PreAccessMask{};

	FAccessFlags AccessMask{};

	FDependencyFlags Dependency{};

};

struct FSubpassQueue
{
	FSubpassQueue(TSharedPtr<FSubpass> DefaultSubpass) :
		Root(DefaultSubpass)
	{
	}

	void Hook(TSharedPtr<FSubpass> NextSubpass, TSharedPtr<FSubpass> DependencyToPreSubpass) {}

	void ClearHooks() {}

private:

	TSharedPtr<FSubpass> Root;

	TVector<TSharedPtr<FSubpass>> FollowedSubpasses;
	TVector<TSharedPtr<FSubpassDependency>> Followed;

};

_KANAS_CORE_END

#endif


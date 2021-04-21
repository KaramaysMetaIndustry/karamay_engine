#include "PipelineBase.h"
#include "Core/SpicesRendererGlobal.h"

void PipelineBase::Assembly(PipelineAssemblageInfoBase* Info)
{
	PipelineAssemblageInfo = Info;

}

void PipelineBase::AssociateTo(RenderableObjectBase* RenderableObject)
{
	if (RenderableObject)
	{
		AssociatedRenderableObjects.push_back(RenderableObject);
	}
}

void PipelineBase::UnassociateTo(RenderableObjectBase* RenderableObject)
{
	if (RenderableObject)
	{
		AssociatedRenderableObjects.erase(std::find(AssociatedRenderableObjects.begin(), AssociatedRenderableObjects.end(), RenderableObject));
	}
}

void PipelineBase::PipelineRender(float DeltaTime)
{
	for (auto It = AssociatedRenderableObjects.begin(); It != AssociatedRenderableObjects.end(); ++It)
	{
		auto RenderableObject = *It;
		if (RenderableObject)
		{
			RenderableObject->Render(DeltaTime);
		}
	}
}

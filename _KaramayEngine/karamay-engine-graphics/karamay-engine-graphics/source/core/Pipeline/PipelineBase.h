#pragma once
#include "Public/STL.h"
#include "Core/Abstract/MetaObject/MetaObject.h"

class PipelineAssemblageInfoBase;
class ShaderBase;
class RenderableObjectBase;

class PipelineBase : public MetaObject
{
public:
	PipelineAssemblageInfoBase* PipelineAssemblageInfo;

public:
	virtual void Assembly(PipelineAssemblageInfoBase* Info);

	virtual void PipelineRender(float DeltaTime);

	virtual void AssociateTo(RenderableObjectBase* RenderableObject);

	virtual void UnassociateTo(RenderableObjectBase* RenderableObject);

protected:
	std::vector<RenderableObjectBase*> AssociatedRenderableObjects;

	std::vector<ShaderBase*> Shaders;

};

class PipelineFactory
{
public:
	virtual PipelineBase* CreatePipeline()
	{
		return nullptr;
	}
};


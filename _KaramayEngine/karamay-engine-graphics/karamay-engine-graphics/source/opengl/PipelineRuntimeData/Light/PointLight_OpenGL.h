#pragma once
#include "Core/PipelineRuntimeData/Light/PointLightBase.h"
class PointLight_OpenGL : public PointLightBase
{
public:
	virtual void Install() override;

	virtual void Submit(PipelineBase* AssociatedPipeline) override;

	virtual void Uninstall() override;

public:
	PointLight_OpenGL();
	virtual ~PointLight_OpenGL();
};

class PointLightFactory_OpenGL : public PointLightFactory
{
public:
	virtual PointLightBase* Create() override
	{
		return new PointLight_OpenGL();
	}
};


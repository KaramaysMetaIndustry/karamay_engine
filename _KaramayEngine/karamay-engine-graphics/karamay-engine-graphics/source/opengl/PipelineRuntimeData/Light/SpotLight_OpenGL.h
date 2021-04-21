#pragma once
#include "Core/PipelineRuntimeData/Light/SpotLightBase.h"

class SpotLight_OpenGL : public SpotLightBase
{
public:
	virtual void Install() override;

	virtual void Submit(PipelineBase* AssociatedPipeline) override;

	virtual void Uninstall() override;
};

class SpotLightFactory_OpenGL : public SpotLightFactory
{
public:
	virtual SpotLightBase* Create() override
	{
		return new SpotLight_OpenGL();
	}
};


#pragma once
#include "Core/PipelineRuntimeData/Light/DirectionalLightBase.h"

class DirectionalLight_OpenGL : public DirectionalLightBase
{
public:
	virtual void Install() override;

	virtual void Submit(PipelineBase* AssociatedPipeline) override;

	virtual void Uninstall() override;

public:
	DirectionalLight_OpenGL();
	virtual ~DirectionalLight_OpenGL();
};

class DirectionalLightFactory_OpenGL : public DirectionalLightFactory
{
public:
	virtual DirectionalLightBase* Create() override
	{
		return new DirectionalLight_OpenGL();
	}
};


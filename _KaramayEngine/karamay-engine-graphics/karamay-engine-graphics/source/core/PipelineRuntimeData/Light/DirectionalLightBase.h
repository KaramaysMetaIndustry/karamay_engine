#pragma once
#include "Abstract/LightBase.h"

class DirectionalLightBase : public LightBase
{
public:
	virtual void Install() override;

	virtual void Submit(PipelineBase* AssociatedPipeline) override;

	virtual void Uninstall() override;

public:
	glm::vec3 Direction, Color, Angle;

public:
	DirectionalLightBase();
	virtual ~DirectionalLightBase();
};


class DirectionalLightFactory : public LightFactory
{
public:
	virtual DirectionalLightBase* Create() override
	{
		return new DirectionalLightBase();
	}
};


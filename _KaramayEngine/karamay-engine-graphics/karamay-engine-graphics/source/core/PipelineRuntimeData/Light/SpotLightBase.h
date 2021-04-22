#pragma once
#include "Abstract/LightBase.h"

class SpotLightBase : public LightBase
{
public:
	virtual void Install() override;

	virtual void Submit(PipelineBase* AssociatedPipeline) override;

	virtual void Uninstall() override;

public:
	glm::vec3 Position, Angle, Direction, Color;

	float CosPhy;

public:
	SpotLightBase();
	virtual ~SpotLightBase();
};

class SpotLightFactory : public LightFactory
{
public:
	virtual  SpotLightBase* Create() override
	{
		return new SpotLightBase();
	}
};


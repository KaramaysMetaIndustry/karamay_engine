#pragma once
#include "Abstract/LightBase.h"

class PointLightBase : public LightBase
{
public:
	virtual void Install() override;

	virtual void Submit(PipelineBase* AssociatedPipeline) override;

	virtual void Uninstall() override;

public:
	glm::vec3 Position, Angle, Direction, Color;

	float Constant, Linear, Quadratic;

public:
	PointLightBase();
	virtual ~PointLightBase();
};

class PointLightFactory : public LightFactory
{
public:
	virtual PointLightBase* Create() override
	{
		return new PointLightBase();
	}
};


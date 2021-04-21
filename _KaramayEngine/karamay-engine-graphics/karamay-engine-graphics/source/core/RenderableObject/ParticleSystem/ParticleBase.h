#pragma once
#include "Public/GLM.h"
#include "Core/Abstract/MetaObject/MetaObject.h"

class ParticleBase : public MetaObject
{
public:
	glm::vec3 Position;

	glm::vec3 Velocity;

	glm::vec4 Color;

	float Size;
	
	float Lifetime;

	bool bActive;

public:
	ParticleBase();
	virtual ~ParticleBase();
};

class ParticleFactory : public MetaObject
{
public:
	virtual ParticleBase* Create()
	{
		return new ParticleBase();
	}
};


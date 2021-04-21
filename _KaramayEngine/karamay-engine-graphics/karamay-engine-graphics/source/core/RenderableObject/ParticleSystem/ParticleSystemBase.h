#pragma once
#include "Core\RenderableObject\Abstract\RenderableObjectBase.h"

class ParticleBase;

class ParticleSystemBase : public RenderableObjectBase
{
public:
	virtual void Install() override;

	virtual void Render(float DeltaTime) override;
	
	virtual void Uninstall() override;

	virtual bool IsRenderable() override;

public:
	void SetSystemParams(unsigned int ParticleNum, unsigned int PatchNum);

public:
	std::vector<ParticleBase*> Particles;

protected:
	unsigned int PatchNum;

	std::vector<float> Vertices;

public:
	ParticleSystemBase();
	virtual ~ParticleSystemBase();
};

class ParticleSystemFactory
{
public:
	virtual ParticleSystemBase* Create()
	{
		return nullptr;
	}
};


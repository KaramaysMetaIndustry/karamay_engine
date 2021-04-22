#pragma once
#include "Public/OpenGL.h"
#include "Core/RenderableObject/ParticleSystem/ParticleSystemBase.h"

class ParticleSystem_OpenGL : public ParticleSystemBase
{
public:
	virtual void Install() override;

	virtual void Render(float DeltaTime) override;
	
	virtual void Uninstall() override;

private:
	GLuint vertexArrayObject0, vertexArrayObject1;

	GLuint vertexBufferObject0, vertexBufferObject1;

	GLuint transformFeedbackObject;

	GLuint elementBufferObject;

	bool bZero;

public:
	ParticleSystem_OpenGL();
	virtual ~ParticleSystem_OpenGL();
};

class ParticleSystemFactory_OpenGL : public ParticleSystemFactory
{
public:
	virtual ParticleSystemBase* Create() override
	{
		return new ParticleSystem_OpenGL();
	}
};


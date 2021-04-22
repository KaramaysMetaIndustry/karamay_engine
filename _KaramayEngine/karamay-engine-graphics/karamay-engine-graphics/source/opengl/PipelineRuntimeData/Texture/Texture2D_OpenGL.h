#pragma once
#include "Public/OpenGL.h"
#include "Core/PipelineRuntimeData/Texture/Texture2DBase.h"

class PipelineBase;

class Texture2D_OpenGL : public Texture2DBase
{
public:
	virtual void LoadPixels(const std::string& FilePath) override;

public:
	virtual void Install() override;

	virtual void Submit(PipelineBase* AssociatedPipeline) override;

	virtual void Uninstall() override;

public:
	std::string UniformName;

private:
	unsigned char* data;

	int width, height, nrChannel;

	GLuint TextureObject;

	GLuint Slot;

	GLenum Type;
};

class Texture2DFactory_OpenGL : public Texture2DFactory
{
public:
	virtual Texture2DBase* Create()
	{
		return new Texture2D_OpenGL();
	}
};


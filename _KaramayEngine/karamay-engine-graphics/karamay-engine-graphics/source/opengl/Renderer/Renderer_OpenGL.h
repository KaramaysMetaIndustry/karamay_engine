#pragma once
#include "Public/OpenGL.h"
#include "Core/Renderer/RendererBase.h"

class WindowBase;

class Renderer_OpenGL : public RendererBase
{
public:
	virtual void LoadContext() override;

	virtual void SetViewport(size_t Width, size_t Height) override;

	virtual void Render(float DeltaTime) override;

public:
	Renderer_OpenGL();
	virtual ~Renderer_OpenGL();
};

class RendererFactory_OpenGL : public RendererFactory
{
public:
	virtual RendererBase* Create()
	{
		return new Renderer_OpenGL();
	}
};


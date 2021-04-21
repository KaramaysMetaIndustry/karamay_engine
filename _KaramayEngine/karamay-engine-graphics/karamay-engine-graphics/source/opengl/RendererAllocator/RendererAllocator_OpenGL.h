#pragma once
#include "Public/OpenGL.h"
#include "Core/RendererAllocator/RendererAllocatorBase.h"

class RendererAllocator_OpenGL : public RendererAllocatorBase
{
public:
	virtual void Initialize() override;

private:
	GLuint SlotIndex;

public:
	GLuint GetTexture2DSlot();

public:
	RendererAllocator_OpenGL();
	virtual ~RendererAllocator_OpenGL();
};

class RendererAllocatorFactory_OpenGL : public RendererAllocatorFactory
{
public:
	virtual RendererAllocatorBase* Create() override
	{
		return new RendererAllocator_OpenGL();
	}
};


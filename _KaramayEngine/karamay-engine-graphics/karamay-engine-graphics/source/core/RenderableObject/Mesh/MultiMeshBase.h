#pragma once
#include "Public/STL.h"
#include "Public/GLM.h"

#include "Core/RenderableObject/Abstract/RenderableObjectBase.h"

class MultiMeshBase : public RenderableObjectBase
{
public:
	virtual void Render(float DeltaTime) override;
	
};


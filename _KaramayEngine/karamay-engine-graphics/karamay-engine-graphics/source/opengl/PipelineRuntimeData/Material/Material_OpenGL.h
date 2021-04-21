#pragma once
#include "Core/PipelineRuntimeData/Material/MaterialBase.h"

class Material_OpenGL : public MaterialBase
{
public:
	virtual void Install() override;

	virtual void Submit(PipelineBase* AssociatedPipeline) override;
	
	virtual void Uninstall() override;

public:
	Material_OpenGL();
	virtual ~Material_OpenGL();
};

class MaterialFactory_OpenGL : public MaterialFactory
{
public:
	virtual MaterialBase* Create()
	{
		return new Material_OpenGL();
	}
};


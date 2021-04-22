#pragma once
#include "Core/PipelineRuntimeData/SceneRenderingData/SceneRenderingDataBase.h"
class SceneRenderingData_OpenGL : public SceneRenderingDataBase
{
public:
	virtual void Install() override;

	virtual void Submit(PipelineBase* AssociatedPipeline) override;

	virtual void Uninstall() override;

};

class SceneRenderingDataFactory_OpenGL : public SceneRenderingDataFactory
{
public:
	virtual SceneRenderingDataBase* Create() override
	{
		return new SceneRenderingData_OpenGL();
	}
};


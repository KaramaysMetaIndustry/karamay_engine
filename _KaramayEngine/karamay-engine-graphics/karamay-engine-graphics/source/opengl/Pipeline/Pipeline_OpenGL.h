#pragma once
#include "Core/Pipeline/PipelineBase.h"
#include "Public/OpenGL.h"

class PipelineCommonTool;

class Pipeline_OpenGL : public PipelineBase
{
public:
	virtual void Assembly(PipelineAssemblageInfoBase* Info) override;

	virtual void PipelineRender(float DeltaTime) override;

	virtual void AssociateTo(RenderableObjectBase* RenderableObject) override;

public:
	PipelineCommonTool* CommonTool;

private:
	void CheckState();

private:
	GLuint programObj;

public:
	Pipeline_OpenGL();
	virtual ~Pipeline_OpenGL();
};


class PipelineFactory_OpenGL : public PipelineFactory
{
public:
	virtual PipelineBase* CreatePipeline();
};


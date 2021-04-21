#pragma once
#include "Core/Pipeline/PipelineAssemblageInfoBase.h"

class PipelineAssemblageInfo_OpenGL : public PipelineAssemblageInfoBase
{
public:
	virtual void Format();
};

class PipelineAssemblageInfoFactory_OpenGL : public PipelineAssemblageInfoFactory
{
public:
	virtual PipelineAssemblageInfoBase* Create() override
	{
		return new PipelineAssemblageInfo_OpenGL();
	}
};


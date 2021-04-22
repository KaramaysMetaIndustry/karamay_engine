#pragma once
#include "Public/STL.h"
#include "Public/GLM.h"

#include "Core/PipelineRuntimeData/Abstract/PipelineRuntimeDataBase.h"

class LightBase : public PipelineRuntimeDataBase
{
public:
	LightBase();
	virtual ~LightBase();
};

class LightFactory : public MetaObject
{
public:
	virtual LightBase* Create()
	{
		return nullptr;
	}
};

